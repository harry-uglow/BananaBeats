
#include "defs.h"
#include "pipeline.h"
#include <stdint.h>

// Function to execute one of four possible types of shift
static int32_t executeShift(int32_t value, int shiftType, int amount) {
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

void decode(arm_t *state) {
    instr_t *toDecode = state->instruction;
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
    toDecode->opCode =    (0x01E00000 & fetched) >> 21;
    toDecode->Rn =        (0x000F0000 & fetched) >> 16;
    toDecode->Rd =        (0x0000F000 & fetched) >> 12;
    toDecode->Rs =        (0x00000F00 & fetched) >> 8;
    toDecode->Rm =         0x0000000F & fetched;
    toDecode->offset = 0x00FFFFFF & fetched;
    //toDecode->offset = 0x00000FFF & fetched;


    // Bits 27 through 25 and 7 through 4 can now be used to determine
    // which of the instruction types the fetched instruction is.
    int bits2726 = (0x0C000000 & fetched) >> 26;
    int bits7to4 = (0x000000F0 & fetched) >> 4;
    int multOrData = toDecode->setI | bits7to4;

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
                toDecode->Rd = toDecode->Rn;
                toDecode->Rn = tmp;
            } else {
                toDecode->type = DATA_PROCESS;
            }
    }

    if((DATA_PROCESS == toDecode->type && !toDecode->setI) ||
            (DATA_TRANSFER == toDecode->type && toDecode->setI)) {
        // Operand 2 is a register

        int amount = 0;
        if (toDecode->isRsShift) {
            // Shift by register
            int rsVal = state->registers[toDecode->Rs];
            amount = (0xFF & rsVal);
        } else {
            // Shift by constant
            amount = (0xF80 & fetched) >> 3;
        }

        // get value of int in rm, the shift type and then perform the shift.
        int32_t rmVal = state->registers[toDecode->Rm];
        int shiftType = (0x00000060 & fetched) >> 5;
        toDecode->op2 = executeShift(rmVal, shiftType, amount);
        toDecode->offset = toDecode->op2;
    } else if(DATA_TRANSFER == toDecode->type) {
        // Offset is a 12 bit immediate offset.

        toDecode->offset = 0x00000FFF & fetched;
    } else if(DATA_PROCESS == toDecode->type) {
        // Operand 2 is an immediate value

        int32_t immConst = (0x000000FF & fetched);
        // Calculate the rotation
        int rotation = 2 * ((0x00000F00 & fetched) >> 8);

        // Bitwise rotate right by 'rotation'
        toDecode->op2 = (immConst >> rotation) | (immConst << (32 - rotation));
    }
    return;
}

void fetch(arm_t *state) {
    int32_t pc = state->registers[REG_PC];
    int32_t *wordSizedMem = (int32_t *)state->memory;
    state->fetched = wordSizedMem[pc / WORD_LENGTH];
}
