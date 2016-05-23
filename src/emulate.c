#include <stdlib.h>
#include <stdio.h>
#include "defs.h"



void printFinalState(arm_t state);


int main(int argc, char **argv) {

	arm_t arm;
	
	// Reading file input for the program	
	FILE *finput = fopen(argv[1],"rb");

	if(finput == NULL) {
	    printf("Could not open %s", argv[1]);
	    return 0;
	}
	
	while(fscanf(finput, "%i", (int *) arm.memory) != EOF) {
	    continue;
	}

	fclose(finput);
	// Finished reading file input	
	

	printFinalState(arm);	

	

	 return EXIT_SUCCESS;

}






void printFinalState(arm_t state) {
	
	printf("Registers:\n");

    int pc   = state.registers[REG_PC];
    int cpsr = state.registers[REG_CPSR];

	// Print out contents of registers 0-9
    for(int i = 0; i < 10; i++) {
    	printf("$%i  :%12d (0x%08x)\n", i, state.registers[i], (unsigned int)  state.registers[i]); 
    }
	
	// Print out contents of registers 10-12
	for(int j = 0; j < 13; j++) {
		printf("$%i :%12d (0x%08x)\n", j, state.registers[j], (unsigned int) state.registers[j]);
	}

	// Print out contents of PC and CPSR
    printf("PC  :%12d (0x%08x)\n", pc, (unsigned int) pc);
    printf("CPSR:%12d (0x%08x)\n", cpsr, (unsigned int) cpsr);
    
	// Print out non-zero contents of memory
	printf("Non-zero memory:\n");

    int k = 0;

	while(state.memory[k*4] != 0) {
    	printf("0x%08x: 0x%08x\n", k*4, (state.memory[k*4]));
        k++;
	}

}


