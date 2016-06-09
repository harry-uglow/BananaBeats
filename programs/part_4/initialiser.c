#include <stdio.h>
#include <string.h>
#include "utils.h" 
#define NUM_OF_INSTRUMENTS 3
#define NUM_OF_SOUNDFILES 12
#define MAX_DIGITS_NUMBER_OF_MODES 15
#define MAX_DIGITS_NUMBER_OF_SOUNDS 3
#define MAX_LENGTH_FILEPATH_STRING 100

// Array of symbol tables as global variable
symbolTable_t *set[NUM_OF_INSTRUMENTS];

// Initialise array of symbol tables for each sound set (instrument)
static void initialiseSymbolTables(void) {
	for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
		set[i] = SymbolTable_new();
	}
    
    char* filePathToFolder = "sounds/set";
    char modeNumber[MAX_DIGITS_NUMBER_OF_MODES];
    char soundNumber[MAX_DIGITS_NUMBER_OF_SOUNDS];
    char* fileExtension = ".wav";
    char filePathToSound[MAX_LENGTH_FILEPATH_STRING];
	// Insert pin-sound entries into each symbol table for each instrument
	for(int j = 0; j < NUM_OF_INSTRUMENTS; j++) { // For each sound mode
        sprintf(modeNumber, "%d/", j);
		for(int k = 0; k < NUM_OF_SOUNDFILES; k++) {
            sprintf(soundNumber, "%d", k);
            strcpy(filePathToSound, filePathToFolder);
            strcat(filePathToSound, modeNumber);
            strcat(filePathToSound, soundNumber);
            strcat(filePathToSound, fileExtension);
            SymbolTable_put(&k, filePathToSound, set[j]);
		} 
	}
}


static void freeSymbolTables(void) {
	for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
		SymbolTable_delete(set[i]);
	}
}

int main() {
    initialiseSymbolTables();
    freeSymbolTables();
    return 0;
}
