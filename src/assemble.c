#include "assembler/utils.h"

int main(int argc, char **argv) {
	// Initialise array of assembly instructions on heap
	// and create symbol table
	if(!initialiseAssembler()) {
		return EXIT_FAILURE;
	}	

	// Read assembler file input 
	if(!firstPass(argv)) {
		return EXIT_FAILURE;
	}

	secondPass();


	// Write results of assembler to binary file specified by 2nd argument
	if(!writeToBinaryFile(argv)) {
		return EXIT_FAILURE;			
	}
	
	// Null check before clearing heap memory
	if(instruction != NULL) {
		free(instruction);
	}


    // TODO: Clear all memory including symbol tables
	return EXIT_SUCCESS;
}
