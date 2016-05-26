#include <stdio.h>
#include "utils.h"

int readFile(assIns_t *instructions, char **argv) {
	// Reading assembly file input
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

int initialiseAssembler(void) {
	// Allocate memory onto the heap for an array of instructions
	assIns_t *instructions = malloc(sizeof(assIns_t) * MEM_SIZE);
	
	// Check if memory allocation failed
	if(instructions == NULL) {
		printf("Memory could not be allocated onto the heap.\n");
		return 0;
	}
 	
	// TODO: Finish complete initialisation of assembler 
}
