#ifndef initialiser_h
#define initialiser_h

#include <stdio.h>
#include <string.h>
#include "symbolTable.h"

// Define numeric constants
#define NUM_OF_SOUNDFILES 12
#define MAX_DIGITS_NUMBER_OF_MODES 15
#define MAX_DIGITS_NUMBER_OF_SOUNDS 3
#define MAX_LENGTH_FILEPATH_STRING 100
#define NUM_OF_INSTRUMENTS 3

// Array of symbol tables as global variable
symbolTable_t *set[NUM_OF_INSTRUMENTS];

// Initialise array of symbol tables for each sound set (instrument)
void initialiseSymbolTables(void);

void freeSymbolTables(void);

#endif
