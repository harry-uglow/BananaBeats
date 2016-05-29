#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "defs.h"

int readFile(assIns_t *instructions, char **argv) {
	// Open file to read from
	FILE *finput = fopen(argv[1],"r");
	
	// Check if assembly file cannot be opened
	if (finput == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 0;
	}


	// TODO: code for reading strings of each assembly instruction

	// Finished reading input of assembly file
	fclose(finput);
	return 1;
}

int initialiseAssembler(assIns_t *instructions) {
	// Allocate memory onto the heap for an array of instructions
	instructions = calloc(MEM_SIZE, sizeof(assIns_t));
	
	// Check if memory allocation failed
	if(instructions == NULL) {
		printf("Memory could not be allocated onto the heap.\n");
		return 0;
	}	
	return 1;
}

int writeToBinaryFile(int32_t *binInstructions, char **argv) {
	// Open file to write to
	FILE *foutput = fopen(argv[2], "wb");

	// Check if file cannot be opened
	if(foutput == NULL) {
		printf("Could not open file %s\n", argv[2]);
		return 0;
	}
	
	// Write all of the binary instructions encoded into the output file
	int pos = 0;
	while(TRUE) {
		int out = fwrite(&binInstructions[pos], sizeof(int32_t), 1, foutput);
		if(out != 1) {
			break;
		}
		pos++;
	}

	// Finished writing to output of binary file
	fclose(foutput); 
	return 1;
}

int isLabel(char *str) {
	// Loop through the string checking for label symbol
	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == ':') {
			return 1;
		}
	}
	return 0;
}
