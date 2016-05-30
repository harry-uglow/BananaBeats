#include "utils.h"

int main(int argc, char **argv) {
    address = 0;

    // Initialise the symbol table
    table = SymbolTable_new();

	// Initialise array of assembly instructions on heap
	if(!initialiseAssembler(instructions, table)) {
		return EXIT_FAILURE;
	}	

	// Read assembler file input 
	if(!firstPass(instructions, &argv[1], table, &address)) {
		return EXIT_FAILURE;
	}

	secondPass(instructions);


	// Write results of assembler to binary file specified by 2nd argument
	if(!writeToBinaryFile(memory, argv)) {
		return EXIT_FAILURE;			
	}
	
	// Null check before clearing heap memory
	if(instructions != NULL) {
		free(instructions);
	}


    // TODO: Clear all memory including symbol tables
	return EXIT_SUCCESS;
}
