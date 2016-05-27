#include <stdio.h>
#include "utils.h"

int readFile(assIns_t *instructions, char **argv) {
	// Open file to read frmo
	FILE *finput = fopen(argv[1],"r");
	
	// Check if assembly file cannot be opened
	if (finput == NULL) {
		printf("Could not open %s\n", argv[1]);
		return 0;
	}
	
	// TODO: code for reading strings of each assembly instruction

	// Finished reading input of assembly file
	fclose(finput);
	return 1;
}

int initialiseAssembler(assIns_t *instructions) {
	// Allocate memory onto the heap for an array of instructions
	instructions = malloc(sizeof(assIns_t) * MEM_SIZE);
	
	// Check if memory allocation failed
	if(instructions == NULL) {
		printf("Memory could not be allocated onto the heap.\n");
		return 0;
	}
 	
	// TODO: Finish complete initialisation of assembler 
}

int writeToBinaryFile(int8_t *binInstructions, char **argv) {
	// Open file to write to
	FILE *foutput = fopen(argv[2]
}

int clearHeap(assIns_t *instructions) {
	free(instructions);
}
