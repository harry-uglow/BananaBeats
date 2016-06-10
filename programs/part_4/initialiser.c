#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "initialiser.h"

// Initialise array of symbol tables for each sound set (instrument)
void initialiseSymbolTables(void) {
    // Allocate heap memory for each symbol table
    for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
        set[i] = SymbolTable_new();
    }
    
    // Insert pin-sound entries into each symbol table for each instrument
    for(int j = 0; j < NUM_OF_INSTRUMENTS; j++) { // For each sound mode
        for(int k = 0; k < NUM_OF_SOUNDFILES; k++) {
            char *filePathToFolder = "sounds/set";
            char modeNumber[MAX_DIGITS_NUMBER_OF_MODES];
            char soundNumber[MAX_DIGITS_NUMBER_OF_SOUNDS];
            char *fileExtension = ".wav";
            char filePathToSound[MAX_LENGTH_FILEPATH_STRING];

            sprintf(modeNumber, "%d/", j);
            sprintf(soundNumber, "%d", k);
            strcpy(filePathToSound, filePathToFolder);
            strcat(filePathToSound, modeNumber);
            strcat(filePathToSound, soundNumber);
            strcat(filePathToSound, fileExtension);
            char *toPut = malloc(sizeof(filePathToSound));
            strcpy(toPut, filePathToSound);
            SymbolTable_put(k, toPut, set[j]);
        } 
    }
}

void freeSymbolTables(void) {
    // Iterate through array of symbol tables and delete
    for(int i = 0; i < NUM_OF_INSTRUMENTS; i++) {
        SymbolTable_delete(set[i]);
    }
}
