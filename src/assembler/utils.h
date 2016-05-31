#ifndef ARM11_19_ASSEMBLER_UTILS_H
#define ARM11_19_ASSEMBLER_UTILS_H

#include "encodeInstructions.h"

int firstPass(char **argv);
int initialiseAssembler();
int writeToBinaryFile(char **argv);
int isLabel(char *str);
void secondPass();
void removeNewline(char *token);
int checkBrackets(char *token, char *temp);
void freeInstructions(void);

#endif //ARM11_19_ASSEMBLER_UTILS_H
