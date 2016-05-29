#include "defs.h"

int32_t encodeDataProcessing(instr_t *instr) {
    int cond = instr->cond;
    int setI = instr->setI;
    int opCode = instr->opCode;
    int setS = instr->setS;
    int Rn = instr->Rn;
    int Rd = instr->Rd;
    int operand2 = 0;

    // Calculate shift
    if (setI) {
        operand2 = instr->immVal;
        operand2 |= (instr->shiftAmount) << IMMVAL_SHIFTAMOUNT_BITS;
    } else {
        int shift = instr->isRsShift;
        shift |= (instr->shiftType) << SHIFT_TYPE_BITS;
        operand2 = instr->Rm;
        if (instr->isRsShift) {
            // Shift by Rs
            shift |= (instr->Rs) << SHIFT_RS_BITS;
        } else {
            // Shift by constant
            shift |= (instr->shiftAmount) << REG_SHIFTAMOUNT_BITS;
        }
        operand2 |= shift << SHIFT_BITS;
    }

    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << COND_BITS;
    binaryInstr |= setI << I_BIT;
    binaryInstr |= opCode << OPCODE_BITS;
    binaryInstr |= setS << S_BIT;
    binaryInstr |= Rn << RN_BITS;
    binaryInstr |= Rd << RD_BITS;
    binaryInstr |= operand2;

    return binaryInstr;
}


int32_t encodeMultiply(instr_t *instr) {
    int cond = instr->cond;
    int setA = instr->setA;
    int setS = instr->setS;
    int Rd = instr->Rn;
    int Rn = instr->Rd;
    int Rs = instr->Rs;
    int Rm = instr->Rm;

    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << COND_BITS;
    binaryInstr |= setA << A_BIT;
    binaryInstr |= setS << S_BIT;
    binaryInstr |= Rd << RD_BITS;
    binaryInstr |= Rn << RN_BITS;
    binaryInstr |= Rs << RS_BITS;
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
   
    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << COND_BITS;
    binaryInstr |= SDT_PREDEFINED_BITS;
    binaryInstr |= setI << I_BIT;
    binaryInstr |= setP << P_BIT;
    binaryInstr |= setU << U_BIT;
    binaryInstr |= setL << L_BIT;
    binaryInstr |= Rn << RN_BITS;
    binaryInstr |= Rd << RD_BITS;
    binaryInstr |= offset;

    return binaryInstr;
}


int32_t encodeBranch(instr_t *instr) {
    int cond = instr->cond;
    int offset = instr->offset;
   
    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= cond << COND_BITS;
    binaryInstr |= BRANCH_PREDEFINED_BITS;
    binaryInstr |= offset;

    return binaryInstr;
}

int32_t encode(instr_t *instr) {
    int32_t binaryInstruction = 0;
    exec_t instructionType = instr->type;

    switch(instructionType) {
        case DATA_PROCESS:
            binaryInstruction = encodeDataProcessing(instr);
            break;

        case MULTIPLY:
            binaryInstruction = encodeMultiply(instr);
            break;

        case DATA_TRANSFER:
            binaryInstruction = encodeSingleDataTransfer(instr);
            break;

        case BRANCH:
            binaryInstruction = encodeBranch(instr);
            break;

        case HALT:
            binaryInstruction = HALT_PREDEFINED_INSTRUCTION;
            break;
    }

    return binaryInstruction;
}
