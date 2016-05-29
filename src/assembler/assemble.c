#include <stdlib.h>
#include "utils.h"

int main(int argc, char **argv) {
	// Declare pointer to array of instructions  
	assIns_t *instructions;

	// Initialise array of assembly instructions on heap
	if(!initialiseAssembler(instructions)) {
		return EXIT_FAILURE;
	}	

	// Read assembler file input 
	if(!readFile(instructions, argv[1])) {
		return EXIT_FAILURE;
	}	

	

	// TODO: Main assembler functions



	// Write results of assembler to binary file specified by 2nd argument
	if(!writeToBinaryFile(binInstructions, argv)) {
		return EXIT_FAILURE;			
	}
	
	// Null check before clearing heap memory
	if(instructions != NULL) {
		free(instructions);
	}

	return EXIT_SUCCESS;
}
