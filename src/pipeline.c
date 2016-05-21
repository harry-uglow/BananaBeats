//
// Created by Harry on 21/05/2016.
//

#include "pipeline.h"
#include "defs.h"
#include <stdint.h>

void decode(arm_t *state) {
    instr_t toDecode = state->instruction;
    int32_t fetched = state->fetched;
    toDecode->cond = (0xF0000000 & fetched) >> 28;
    int bits2726 = (0x0C000000 & fetched) >> 26;
    switch (bits2726) {
        case 2 :
            // Branch case
            toDecode->type = BRANCH;
            toDecode->offset = 0x00FFFFFF & fetched;
            break;

        case 1 :
            // Single Data Transfer
            toDecode->type = DATA_TRANSFER;
            toDecode->setI = 0x02000000 & fetched;
            toDecode->setP = 0x01000000 & fetched;
            toDecode->setU = 0x00800000 & fetched;
            toDecode->setL = 0x00100000 & fetched;
            toDecode->Rn = (0x000F0000 & fetched) >> 16;
            toDecode->Rd = (0x0000F000 & fetched) >> 12;
            toDecode->offset = 0x00000FFF & fetched;
            break;
    }
    // At this point we know S must be set
    toDecode->setS = 0x00100000 & fetched;
    // Bits 25 and 7 through 4 can now be used to determine which of the two
    // remaining instruction types the fetched instruction is.
    toDecode->setI = (0x02000000 & fetched) >> 20;
    int bits7to4 = (0x000000F0 & fetched) >> 4;
    int multOrData = setI | bits7to4;
    // Multiply case
    if (9 == multOrData) {
        toDecode->type = MULTIPLY;
        toDecode->setA = 0x00200000 & fetched;
        toDecode->Rd = (0x00F0000 & fetched) >> 16;
        toDecode->Rn = (0x0000F000 & fetched) >> 12;
        toDecode->Rs = (0x00000F00 & fetched) >> 8;
        toDecode->Rm = 0x0000000F & fetched;
    } else {
        toDecode->type = DATA_PROCESS;
        toDecode->opcode = (0x01E00000 & fetched) >> 21;
        toDecode->Rn = (0x000F0000 & fetched) >> 16;
        toDecode->Rd = (0x0000F000 & fetched) >> 12;
        toDecode->op2 = 0x00000FFF & fetched;
    }
    return;
}