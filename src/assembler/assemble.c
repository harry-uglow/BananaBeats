#include "utils.h"

int main(int argc, char **argv) {
	// Declare pointer to array of instructions  
	// and address counter and symbol table
	assIns_t *instructions;
    address = 0;

    // Initialise the symbol table
    table = SymbolTable_new;

	// Initialise array of assembly instructions on heap
	if(!initialiseAssembler(instructions, table)) {
		return EXIT_FAILURE;
	}	

	// Read assembler file input 
	if(!firstPass(instructions, argv[1], table, &address)) {
		return EXIT_FAILURE;
	}	

	

	// TODO: Main assembler functions
    // Loop through the array of assembly instructions calling get format and 
    // encode on each. Translate the labels into loops using the symbolTable


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
