#ifndef ARM11_19_UTILS_H
#define ARM11_19_UTILS_H

#include <stdint.h>

int32_t executeShift(int32_t value, int shiftType, int amount);
int checkCond(int cond, int NZCV);

#endif //ARM11_19_UTILS_H
