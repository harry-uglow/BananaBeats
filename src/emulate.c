#include <stdlib.h>
#include <stdio.h>
#include "defs.h"



void printFinalState(arm_t state);


int main(int argc, char **argv) {
	
	arm_t arm;

    // Assign memory array onto heap
    int8_t *memory = calloc(MEM_SIZE, sizeof(int8_t));
    if (memory == NULL) {
        printf("Failed to create memory array on heap");
        return 0;
    }

    // Assign registers array onto heap
    int32_t *registers = calloc(NUMBER_OF_REGISTERS, sizeof(int32_t));
    if (registers == NULL) {
        printf("Failed to create registers array on heap");
        return 0;
    }

    // Point the arm state to register and memory arrays on the heap
    arm.memory = memory;
    arm.registers = registers;

	// Reading file input 	
	FILE *finput = fopen(argv[1],"rb");

	if(finput == NULL) {
	    printf("Could not open %s", argv[1]);
	    return 0;
	}
	
	// Loop to read binary file, one byte at a time,
	// and copy the bytes into processor's memory until
	// there are no more bytes left to read in the file
	int8_t byteInput; // Temporary byte variable which stores the read byte on each iteration of the loop
 	int8_t *pByteInput = &byteInput;
	int memPos = 0;
	while(1) {
		int in = fread(pByteInput,sizeof(int8_t),1,finput);
	   	if(in != 1) {
			break;
		}
		arm.memory[memPos] = byteInput;
		memPos++;
	}
	fclose(finput);
	// Finished reading file input

	printFinalState(arm);

    // Clear memory and register arrays
    if (memory != NULL) {
        free(memory);
    }
    if (registers != NULL) {
        free(registers);
    }

	return EXIT_SUCCESS;

}

void printFinalState(arm_t state) {
	
	printf("Registers:\n");

    int pc   = state.registers[REG_PC];
    int cpsr = state.registers[REG_CPSR];

	// Print out contents of registers 0-9
    for(int i = 0; i < 10; i++) {
    	printf("$%i  :%12d (0x%08x)\n", i, state.registers[i], state.registers[i]); 
    }
	
	// Print out contents of registers 10-12
    for(int j = 0; j < 13; j++) {
		printf("$%i :%12d (0x%08x)\n", j, state.registers[j], state.registers[j]);
	}

	// Print out contents of PC and CPSR
    printf("PC  :%12d (0x%08x)\n", pc, pc);
    printf("CPSR:%12d (0x%08x)\n", cpsr, cpsr);
    
	// Print out non-zero contents of memory
	printf("Non-zero memory:\n");

    int k = 0;

	while(state.memory[k*4] != 0) {
    	printf("0x%08x: 0x%08x\n", k*4, (state.memory[k*4]));
        k++;
	}

}


