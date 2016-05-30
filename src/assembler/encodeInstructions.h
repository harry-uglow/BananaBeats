#ifndef ARM11_19_ENCODEINSTRUCTIONS_H
#define ARM11_19_ENCODEINSTRUCTIONS_H

#include <stdint.h>
#include "getFormat.h"

int address;
int8_t *memory;

int32_t encode(assIns_t *instr);

#endif //ARM11_19_ENCODEINSTRUCTIONS_H
