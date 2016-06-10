#include "assembler/utils.h"

int main(int argc, char **argv) {
    // Initialise array of assembly instructions on heap
    // and create symbol table
    if (!initialiseAssembler()) {
        return EXIT_FAILURE;
    }    

    // Read assembler file input and execute first pass 
    if (!firstPass(argv)) {
        return EXIT_FAILURE;
    }

    // Execute second pass
    secondPass();

    // Write results of assembler to binary file specified by 2nd argument
    if (!writeToBinaryFile(argv)) {
        return EXIT_FAILURE;            
    }

    // Free memory components of instructions array from heap
    freeInstructions();
    
    // Null check before clearing heap memory
    if (instruction != NULL) {
        free(instruction);
    }

    // Delete the symbol table after use
    SymbolTable_delete(&table);
    return EXIT_SUCCESS;
}
