#ifndef ARM11_19_UTILS_H
#define ARM11_19_UTILS_H

int32_t executeShift(int32_t value, int shiftType, int amount);
int checkCond(int cond, int NZCV);
int initialiseProcessor(arm_t *state);
int readFile(arm_t *state, char **argv);
void printFinalState(arm_t *state);

#endif //ARM11_19_UTILS_H
