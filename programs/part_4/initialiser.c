#include <stdio.h>
#include "utils.h" 
#define NUM_OF_INSTRUMENTS 3
#define NUM_OF_SOUNDFILES 12

// Symbol table array as global variable
symbolTable_t *set[NUM_OF_INSTRUMENTS];

static void initialiseSymbolTables(void) {
	// Initialise array of symbol tables for each sound set (instrument) 
	for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
		set[i] = SymbolTable_new();
	}

	// Insert pin-sound entries into each symbol table for each instrument
	for(int j = 0; j < NUM_OF_INSTRUMENTS; j++) {
 		
		for(int k = 0; j < NUM_OF_SOUNDFILES; j++) {
		} 
	}
}

static void freeSymbolTables(void) {
	for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
		SymbolTable_delete(set[i]);
	}
}
