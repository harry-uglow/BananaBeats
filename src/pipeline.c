
#include "pipeline.h"
#include "defs.h"
#include <stdint.h>

void decode(arm_t *state) {
    instr_t toDecode = state->instruction;
    int32_t fetched = state->fetched;

    // Sections of the instruction to be used as variables are selected and set
    // here. Where actual values will matter are required the result is shifted
    // to the end where necessary. In the case of "set" variables, these will
    // be used as booleans and no shift is required. The exception is "setI"
    // which is used later in this function to determine instruction type.
    toDecode->cond =      (0xF0000000 & fetched) >> 28;
    toDecode->setI =      (0x02000000 & fetched) >> 20;
    toDecode->setP =       0x01000000 & fetched;
    toDecode->setU =       0x00800000 & fetched;
    toDecode->setL =       0x00100000 & fetched;
    toDecode->setS = toDecode->setL;
    toDecode->setA =       0x00200000 & fetched;
    toDecode->isRsShift =  0x00000010 & fetched;
    toDecode->opcode =    (0x01E00000 & fetched) >> 21;
    toDecode->Rn =        (0x000F0000 & fetched) >> 16;
    toDecode->Rd =        (0x0000F000 & fetched) >> 12;
    toDecode->Rs =        (0x00000F00 & fetched) >> 8;
    toDecode->Rm =         0x0000000F & fetched;
    toDecode->shiftType = (0x00000060 & fetched) >> 5;
    toDecode->offset = 0x00FFFFFF & fetched;
    //toDecode->offset = 0x00000FFF & fetched;


    // Bits 27 through 25 and 7 through 4 can now be used to determine
    // which of the instruction types the fetched instruction is.
    int bits2726 = (0x0C000000 & fetched) >> 26;
    int bits7to4 = (0x000000F0 & fetched) >> 4;
    int multOrData = setI | bits7to4;

    switch (bits2726) {
        case 2 :
            toDecode->type = BRANCH;
            break;
        case 1 :
            toDecode->type = DATA_TRANSFER;
            break;
        default:
            if(9 == multOrData) {
                toDecode->type = MULTIPLY;
                // In this case Rd and Rn must be swapped
                int32_t tmp = toDecode->Rd;
                toDecode->Rd = toDecode->Rn
                toDecode->Rn = tmp;
            } else {
                toDecode->type = DATA_PROCESS;
            }
    }

    //TODO: Beyond this point. -HARRY 22/05/16 15:23
    if(DATA_PROCESS == toDecode->type && !toDecode->setI ||
            DATA_TRANSFER == toDecode->type && toDecode->setI) {
        // Get register Rm
        int rm = (0xF & fetched);
        // Get shift value
        int shift = ((0xFF0 & fetched) >> 4);
        // Get shift type
        int shiftType = ((0x06 & shift) >> 1);

        // get value of int in rm
        int32_t rmVal = state->registers[rm];

        int32_t shiftedVal = 0;

        // Check if bit 4 is set
        if (0x1 & shift) {
            int rs = (0xF0 & shift) >> 4;
            int rsVal = state->registers[rs];
            int amount = (0xFF & rsVal);
            shiftedVal = executeShift(rmVal, shiftType,  amount);
        } else {
            int amount = (0xF8 & shift) >> 3;
            shiftedVal = executeShift(rmVal, shiftType, amount);
        }
    }
    return;
}

// Function to execute the shift dependent upon the type
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