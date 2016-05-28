#include "getFormat.h"
#include "defs.h"
#include <stdint.h>
#include <string.h>

void setCond(instr_t *ins);
void getFormDatProc(instr_t *ins);
void getFormMult(instr_t *ins);
void getFormDatTran(instr_t *ins);
void getFormBranch(instr_t *ins);

// Function intended to fill the necessary formatting fields in
// struct Instruction to aid encoding.
instr_t getFormat(assInstr_t *assIns) {
    // Initialise instr_t for output later.
    instr_t out;
    out.opMnemonic = mnemonicStringToEnum(assIns->mnemonic);

    setCond(out);

    if(out.opMnemonic <= MAX_DATA_PROCESS) {
        out.type == DATA_PROCESS;
        getFormDatProc(&out, assIns);
    } else if(out.opMnemonic <= MAX_MULTIPLY) {
        out.type == MULTIPLY;
        getFormMult(&out, assIns);
    } else if(out.opMnemonic <= MAX_DATA_TRANSFER) {
        out.type == DATA_TRANSFER;
        getFormDatTran(&out, assIns);
    } else if(out.opMnemonic <= MAX_BRANCH) {
        out.type == BRANCH;
        getFormBranch(&out, assIns);
    } else {
        out.type == HALT;
    }


    // TODO : Continue implementation of getFormat()
}

mnemonic_t mnemonicStringToEnum(char mnemonic[]) {
    return ADD;
    /*For this function I intend to have an ordered table mapping
      a mnemonic's string representation to its mnemonic_t enum representation.
      For example map "add" to ADD. Then this function simply has to iterate
      through the key's of this table using strcmp until it either finds the key
      being looked for or goes past it. If the string is found, return the
      mapping, else throw an invalid assembly instruction error.
    */
}

void setCond(instr_t *ins) {
    if (ins->opMnemonic <= MIN_BRANCH) {
        ins->cond = ALWAYS;
    } else {
        ins->cond = ins->opMnemonic - BRANCH_OFFSET;
    }
}

void getFormDatProc(instr_t *ins, assIns_t assIns) {
    // Not supporting optional case for now
    ins->setI = 1;

    // The opMnemonic enum is organised such that the numerical values are
    // equal to the opCode values, allowing for this simple code.
    ins->opCode = ins->opMnemonic;

    // S is set for tst, teq and cmp instructions
    if (ins->opMnemonic == TST || ins->opMnemonic == TEQ ||
        lins->opMnemonic == CMP) {
        ins->setS = 1;
    }

    //Reg Rn
    sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", ins->Rn);
}

void getFormMult(instr_t *ins, assIns_t assIns) {
    // Set the Cond
    ins->cond = 14;    // MAGIC NUMBER TO BE DEALT WITH

    // Set A bit
    if (ins->opMnemonic == MUL) {
        ins->setA = 0;
    } else {
        ins->setA = 1;
    }

    // Set S bit
    ins->setS = 0;

    // TODO: Implementing the formatting for the registers
}

void getFormDatTran(instr_t *ins, assIns_t assIns){

}

void getFormBranch(instr_t *ins, assIns_t assIns){

}
