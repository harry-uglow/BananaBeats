#include "encodeInstructions.h"

static int32_t encodeDataProcessing(instr_t *instr);
static int32_t encodeMultiply(instr_t *instr);
static int32_t encodeSingleDataTransfer(instr_t *instr, int16_t currAddress);
static int32_t encodeBranch(instr_t *instr, int16_t currAddress);
static int buildShift(instr_t *instr);

static int32_t encodeDataProcessing(instr_t *instr) {
    int operand2 = 0;
    // Calculate shift
    if (instr->setI) {
        operand2 = instr->Rm & 0x000000FF;
        operand2 |= (instr->shiftAmount) << IMMVAL_SHIFTAMOUNT_BITS;
    } else {
        operand2 = instr->Rm;
        int shift = buildShift(instr);
        operand2 |= shift << SHIFT_BITS;
    }

    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= instr->cond << COND_BITS;
    binaryInstr |= instr->setI << I_BIT;
    binaryInstr |= instr->opCode << OPCODE_BITS;
    binaryInstr |= instr->setS << S_BIT;
    binaryInstr |= instr->Rn << RN_BITS;
    binaryInstr |= instr->Rd << RD_BITS;
    binaryInstr |= operand2;
    return binaryInstr;
}

static int32_t encodeMultiply(instr_t *instr) {
    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= instr->cond << COND_BITS;
    binaryInstr |= instr->setA << A_BIT;
    binaryInstr |= instr->setS << S_BIT;
    binaryInstr |= instr->Rn << RD_BITS;
    binaryInstr |= instr->Rd << RN_BITS;
    binaryInstr |= instr->Rs << RS_BITS;
    binaryInstr |= MULT_PREDEFINED_BITS;
    binaryInstr |= instr->Rm;
    return binaryInstr;
}

static int32_t encodeSingleDataTransfer(instr_t *instr, int16_t currAddress) {
    // If SDT expr, then calculate offset, store it in memory
    if (instr->calculateOffset) {
        // Put this in memory at the end at the position:
        int32_t newExpression = instr->SDTExpression;
        memory[WORD_LENGTH * address] 
                = (int8_t) (MASK_BYTE_0 & newExpression);
        memory[(WORD_LENGTH * address) + 1]
                = (int8_t) ((MASK_BYTE_1 & newExpression) >> 8);
        memory[(WORD_LENGTH * address) + 2]
                = (int8_t) ((MASK_BYTE_2 & newExpression) >> 16);
        memory[(WORD_LENGTH * address) + 3]
                = (int8_t) ((MASK_BYTE_3 & newExpression) >> 24);
        // Calculate offset and override it
        // Address is the next free word in memory
        instr->offset = (WORD_LENGTH * address) - currAddress;
        // Take into account off by 8 effect of ARM pipeline
        instr->offset -= PIPELINE_OFFSET;
        // Increment the address counter and numStoredConstants
        address++;
        numStoredConstants++;
    } else if (instr->setI) {
        // Just in case
        instr->offset = instr->Rm;
        int shift = buildShift(instr);
        instr->offset |= (shift << SHIFT_BITS);
    } else if (instr->offset < 0) {
        instr->setU = 0;
        instr->offset = -instr->offset;
    }

    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= instr->cond << COND_BITS;
    binaryInstr |= SDT_PREDEFINED_BITS;
    binaryInstr |= instr->setI << I_BIT;
    binaryInstr |= instr->setP << P_BIT;
    binaryInstr |= instr->setU << U_BIT;
    binaryInstr |= instr->setL << L_BIT;
    binaryInstr |= instr->Rn << RN_BITS;
    binaryInstr |= instr->Rd << RD_BITS;
    binaryInstr |= instr->offset;
    return binaryInstr;
}

static int32_t encodeBranch(instr_t *instr, int16_t currAddress) {
    int16_t addressDiff
            = (int16_t) ((instr->targetAddress * WORD_LENGTH) - currAddress);
    // Take into account off-by-8 effect of the ARM pipeline.
    addressDiff -= PIPELINE_OFFSET;
    int32_t offset = (addressDiff << OFFSET_SIGN_EXTEND) >> OFFSET_RIGHT_SHIFT;
    offset &= OFFSET_MASK;

    // Build the instruction via bit operations
    int32_t binaryInstr = 0;
    binaryInstr |= instr->cond << COND_BITS;
    binaryInstr |= BRANCH_PREDEFINED_BITS;
    binaryInstr |= offset;
    return binaryInstr;
}

int32_t encode(assIns_t *instr) {
    static int16_t currAddress = 0;
    int32_t binaryInstruction = 0;
    instr_t *format = getFormat(instr);

    switch (format->type) {
        case DATA_PROCESS:
            binaryInstruction = encodeDataProcessing(format);
            break;
        case MULTIPLY:
            binaryInstruction = encodeMultiply(format);
            break;
        case DATA_TRANSFER:
            binaryInstruction = encodeSingleDataTransfer(format, currAddress);
            break;
        case BRANCH:
            binaryInstruction = encodeBranch(format, currAddress);
            break;
        case HALT:
            binaryInstruction = HALT_PREDEFINED_INSTRUCTION;
            break;
    }
    currAddress += WORD_LENGTH;
    return binaryInstruction;
}

static int buildShift(instr_t *instr) {
    int shift = instr->isRsShift;
    shift |= (instr->shiftType) << SHIFT_TYPE_BITS;
    if (instr->isRsShift) {
        // Shift by Rs
        shift |= (instr->Rs) << SHIFT_RS_BITS;
    } else {
        // Shift by constant
        shift |= (instr->shiftAmount) << REG_SHIFTAMOUNT_BITS;
    }
    return shift;
}
