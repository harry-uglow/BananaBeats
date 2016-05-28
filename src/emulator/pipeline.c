#include "executeInstructions.c"
#include "pipeline.h"

// Fetch the instruction from the virtual memory
void fetch(arm_t *state) {
    int32_t pc = state->registers[REG_PC];
    // Pointer to the 32-bit instruction
    int32_t *wordSizedMem = (int32_t *)state->memory;
    // Load instruction into the current state
    state->fetched = wordSizedMem[pc / WORD_LENGTH];
    // Increment program counter register
    state->registers[REG_PC] += WORD_LENGTH;
    state->isFetched = 1;
}

// Decode the fetched instruction
void decode(arm_t *state) {
    instr_t *toDecode = state->instruction;
    int32_t fetched = state->fetched;
    state->isDecoded = 1;

    // Check whether the instruction is 'halt' i.e. all bits are 0
    if(!fetched) {
        toDecode->type = HALT;
        return;
    }
    // Sections of the instruction to be used as variables are selected and
    // set here. Where actual values will matter, the result is shifted
    // to the end. In the case of "set" variables, these will
    // be used as booleans and no shift is required.
    toDecode->cond =      (MASK_COND & fetched) >> COND_LAST;
    toDecode->setI =       MASK_I_BIT & fetched;
    toDecode->setP =       MASK_P_BIT & fetched;
    toDecode->setU =       MASK_U_BIT & fetched;
    toDecode->setA =       MASK_A_BIT & fetched;
    toDecode->setS =       MASK_S_BIT & fetched;
    toDecode->setL =       toDecode->setS;
    toDecode->isRsShift =  MASK_RS_SHIFT_BIT & fetched;
    toDecode->opCode =    (MASK_OPCODE & fetched) >> OPCODE_LAST;
    toDecode->Rn =        (MASK_RN & fetched) >> RN_LAST;
    toDecode->Rd =        (MASK_RD & fetched) >> RD_LAST;
    toDecode->Rs =        (MASK_RS & fetched) >> RS_LAST;
    toDecode->Rm =         MASK_RM & fetched;
    toDecode->shiftType = (MASK_SHIFT_T & fetched) >> SHIFT_T_LAST;

    // If !(bit 25) and bytes 7 through 4 have pattern 1001
    int multOrData = MASK_MULT_DATA & fetched;

    if(MASK_BRANCH & fetched) {
        // If bit 27 is set then we have a Branch Instruction.
        toDecode->type = BRANCH;
        toDecode->offset = MASK_OFF_BRCH & fetched;
    } else if(MASK_SDT & fetched) {
        // If bit 26 is set then it's a Single Data Transfer.
        toDecode->type = DATA_TRANSFER;
        toDecode->offset = MASK_OFF_DATA & fetched;
    } else if(MULT_ID == multOrData) {
        // If !(bit 25) and bytes 7 through 4 have pattern 1001 then
        // it is a Multiply instruction
        toDecode->type = MULTIPLY;
        // In this case Rd and Rn must be swapped
        int tmp = toDecode->Rd;
        toDecode->Rd = toDecode->Rn;
        toDecode->Rn = tmp;
    } else {
        // Otherwise (assuming correctly formed input), we have a Data
        // Processing instruction.
        toDecode->type = DATA_PROCESS;
    }

    if((DATA_PROCESS == toDecode->type && !toDecode->setI) ||
            (DATA_TRANSFER == toDecode->type && toDecode->setI)) {
        // Operand 2 is a register
        if (toDecode->isRsShift) {
            // Shift by register
            int rsVal = state->registers[toDecode->Rs];
            // Shift amount specified by bottom byte of Rs.
            toDecode->shiftAmount = (MASK_END_BYTE & rsVal);
        } else {
            // Shift by constant
            toDecode->shiftAmount = (MASK_SHFT_CONST & fetched)
                                    >> SHIFT_CONST_LAST;
        }
    } else if(DATA_PROCESS == toDecode->type) {
        // Operand 2 is an immediate value
        toDecode->op2 = (MASK_END_BYTE & fetched);
        // Calculate the rotation amount
        toDecode->shiftAmount = 2 * ((MASK_ROTATE & fetched) >> ROT_AMT_LAST);
    }
}

// Execute the decoded instruction
void execute(arm_t *state) {
    int NZCV = (MASK_NZCV & state->registers[REG_CPSR]) >> CPSR_LAST;

    if(checkCond(state->instruction->cond, NZCV)) {
        exec_t type = state->instruction->type;
        if(type == DATA_PROCESS) {
            dataProcessing(state);
        } else if(type == MULTIPLY) {
            multiply(state);
        } else if(type == DATA_TRANSFER) {
            singleDataTransfer(state);
        } else if(type == BRANCH) {
            branch(state);
        }
    }
}

// One iteration of the pipeline cycle
int iteratePipeline(arm_t *state) {
    // Execute if the instruction has been decoded
    if(state->isDecoded) {
        if(state->instruction->type == HALT) {
            return 0;
        }
        execute(state);
    }

    // Decode if the instruction has been fetched
    if(state->isFetched) {
        decode(state);
    }

    // Fetch the next instruction
    fetch(state);
    return 1;
}
