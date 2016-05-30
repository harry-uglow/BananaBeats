#ifndef ARM11_19_ASSEMBLER_UTILS_H
#define ARM11_19_ASSEMBLER_UTILS_H

#include "defs.h"

int firstPass(assIns_t *instructions, char **argv, symbolTable_t *table);
int initialiseAssembler(assIns_t *instructions, symbolTable_t *table);
int writeToBinaryFile(int32_t *instructions, char **argv);
int isLabel(char *str);
int8_t *secondPass(assIns_t *instructions);
void removeNewline(char *token);

#endif //ARM11_19_ASSEMBLER_UTILS_H
