#include <stdint.h>
#include "utils.h"

int32_t executeShift(int32_t value, int shiftType, int amount) {
    int32_t shiftedValue = 0;

    switch (shiftType) {
        // logical shift left
        case 0:
            shiftedValue = value << amount;
            break;

            // logical shift right
        case 1:
            shiftedValue = (int)((unsigned int) value >> amount);
            break;

            // arithmetic shift right
        case 2:
            shiftedValue = value >> amount;
            break;

            // rotate right
        case 3:
            shiftedValue = (value >> amount) | (value << (32 - amount));
            break;

    }
    return shiftedValue;
}

int checkCond(int cond, int NZCV){
    int passesCond = 0;
    switch (cond){
        case 0 :
            // Equal
            passesCond = 0x4 & NZCV;
            break;
        case 1 :
            // Not equal
            passesCond = !(0x4 & NZCV);
            break;
        case 10 :
            // Greater or equal
            passesCond = ((9 == (0x9 & NZCV)) || !(0x9 & NZCV));
            break;
        case 11 :
            // Less than
            passesCond = ((1 == (0x9 & NZCV)) || (8 == (0x9 & NZCV)));
            break;
        case 12 :
            // Greater than
            passesCond = (!(0x4 & NZCV) &&
                          ((9 == (0x9 & NZCV)) || !(0x9 & NZCV)));
            break;
        case 13 :
            // Less than or equal
            passesCond = ((0x4 & NZCV) ||
                          ((1 == (0x9 & NZCV)) || (8 == (0x9 & NZCV))));
            break;
        case 14 :
            // Always
            passesCond = 1;
            break;
    }
    return passesCond;
}