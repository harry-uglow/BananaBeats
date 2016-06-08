#include <stdio.h>
#include "utils.h" 

static symbolTable_t *initialiseSymbolTables(void) {
	// Initialise array of symbol tables for each sound set (instrument) 
	symbolTable_t set[3];
	set[0] = SymbolTable_new();
	set[1] = SymbolTable_new();
	set[2] = SymbolTable_new();

	// TODO: Insert correct pin and sound values into symbol table once the sound files are added into sounds folder
		
	return set;
}

static void freeSymbolTables(symbolTable_t set[], int num_of_instruments) {
	for(int i = 0; i < num_of_instruments; i++) {
		SymbolTable_delete(&set[i]);
	}
}
