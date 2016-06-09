#ifndef ARM11_19_ENCODEINSTRUCTIONS_H
#define ARM11_19_ENCODEINSTRUCTIONS_H

#include "getFormat.h"

// Global variables
int address;
int numStoredConstants;
int8_t *memory;
assIns_t *instruction;

int32_t encode(assIns_t *instr);

#endif //ARM11_19_ENCODEINSTRUCTIONS_H
