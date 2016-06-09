#ifndef initialiser_h
#define initialiser_h

#include <stdio.h>
#include <string.h>
#include "soundsTable.h"

// Initialise array of symbol tables for each sound set (instrument)
void initialiseSymbolTables(void);

void freeSymbolTables(void);

#endif