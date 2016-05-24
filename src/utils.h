#ifndef ARM11_19_UTILS_H
#define ARM11_19_UTILS_H

#include <stdint.h>
#include "defs.h"
#include "pipeline.h"


int32_t executeShift(int32_t value, int shiftType, int amount);
int checkCond(int cond, int NZCV);
void initialiseProcessor(arm_t *state);
void readFile(arm_t *state, char **argv);
int iteratePipeline(arm_t *state);
void printFinalState(arm_t *state);

#endif //ARM11_19_UTILS_H
