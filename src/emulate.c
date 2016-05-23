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

    for(int i = 0; i < 13; i++) {
    	printf("$%i  :          %d (0x%x)\n", i, state.registers[i], (unsigned int)  state.registers[i]); 
    }
    printf("PC  :          %d (0x%08x)\n", pc, (unsigned int) pc);
    printf("CPSR:          %d (0x%08x)\n", cpsr, (unsigned int) cpsr);
    printf("Non-zero memory:\n");

    int j = 0;

	while(state.memory[j*4] != 0) {
    	printf("0x%08x: 0x%08x\n", j*4, (state.memory[j*4]));
        j++;
	}

}


