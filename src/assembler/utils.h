#ifndef ARM11_19_ASSEMBLER_UTILS_H
#define ARM11_19_ASSEMBLER_UTILS_H

#include "encodeInstructions.h"

int firstPass(assIns_t *instructions, char **argv, symbolTable_t *table);
int initialiseAssembler(assIns_t *instructions, symbolTable_t *table);
int writeToBinaryFile(int8_t *instructions, char **argv);
int isLabel(char *str);
void *secondPass(assIns_t *instructions);
void removeNewline(char *token); // TODO: This is unused

#endif //ARM11_19_ASSEMBLER_UTILS_H
