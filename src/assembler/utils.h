#ifndef ARM11_19_ASSEMBLER_UTILS_H
#define ARM11_19_ASSEMBLER_UTILS_H

#include "defs.h"

int readFile(assIns_t *instructions, char **argv);
int initialiseAssembler(assIns_t *instructions);
int writeToBinaryFile(int32_t *instructions, char **argv);
int isLabel(char *str);

#endif //ARM11_19_ASSEMBLER_UTILS_H
