#include "defs.h"

int32_t encodeDataProcessing(instr_t *instr) {
    int cond = instr->cond;
    int setI = instr->setI;
    int opCode = instr->opCode;
    int setS = instr->setS;
    int Rn = instr->Rn;
    int Rd = instr->Rd;
    int operand2 = instr->op2;

    // Build the instruction via accumulation and bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << 28;
    binaryInstr |= setI << 25;
    binaryInstr |= opCode << 21;
    binaryInstr |= setS << 20;
    binaryInstr |= Rn << 16;
    binaryInstr |= Rd << 12;
    binaryInstr |= operand2;

    return binaryInstr;
}


int32_t encodeMultiply(instr_t *instr) {
    int cond = instr->cond;
    int setA = instr->setA;
    int setS = instr->setS;
    int Rd = instr->Rd;
    int Rn = instr->Rn;
    int Rs = instr->Rs;
    int Rm = instr->Rm;

    // Build the instruction via accumulation and bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << 28;
    binaryInstr |= setA << 21;
    binaryInstr |= setS << 20;
    binaryInstr |= Rd << 16;
    binaryInstr |= Rn << 12;
    binaryInstr |= Rs << 8;
    binaryInstr |= MULT_PREDEFINED_BITS;    
    binaryInstr |= Rm;

    return binaryInstr;
}


int32_t encodeSingleDataTransfer(instr_t *instr) {
    int cond = instr->cond;
    int setI = instr->setI;
    int setP = instr->setP;
    int setU = instr->setU;
    int setL = instr->setL;
    int Rn = instr->Rn;
    int Rd = instr->Rd;
    int offset = instr->offset;
   
    // Build the instruction via accumulation and bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << 28;
    binaryInstr |= SDT_PREDEFINED_BITS;
    binaryInstr |= setI << 25;
    binaryInstr |= setP << 24;
    binaryInstr |= setU << 23;
    binaryInstr |= setL << 20;
    binaryInstr |= Rn << 16;
    binaryInstr |= Rd << 12;
    binaryInstr |= offset;

    return binaryInstr;
}


int32_t encodeBranch(instr_t *instr) {
    int cond = instr->cond;
    int offset = instr->offset;
   
    // Build the instruction via accumulation and bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << 28;
    binaryInstr |= BRANCH_PREDEFINED_BITS;
    binaryInstr |= offset;

    return binaryInstr;

}
