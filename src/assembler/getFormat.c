#include "getFormat.h"
#include "defs.h"
#include <stdint.h>
#include <string.h>

// Function intended to fill the necessary formatting fields in
// struct Instruction to aid encoding.
instr_t getFormat(assIns_t *assIns) {
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

void getFormDatProc(instr_t *ins, assIns_t *assIns) {
    // I will not be set unless otherwise specified.
    ins->setI = 0;
    // Not supporting optional case for now means that bit 4 will be 0,
    // the shiftType is irrelevant and the shift amount should be 0.
    ins->isRsShift = 0;
    ins->shiftType = 0;
    ins->shiftAmount = 0;
    // S is 0 unless otherwise specifed.
    ins->setS = 0;

    // The opMnemonic enum is organised such that the numerical values are
    // equal to the opCode values, allowing for this simple code.
    ins->opCode = ins->opMnemonic;

    // S is set for tst, teq and cmp instructions
    if (ins->opMnemonic == TST || ins->opMnemonic == TEQ ||
        lins->opMnemonic == CMP) {
        ins->setS = 1;

    // Set up safely allocated pointers for use in sscanf
    int *Rn = malloc(sizeof(int *));
    int *Rd = malloc(sizeof(int *));
    int *Rm = malloc(sizeof(int *));
    int *immVal = malloc(sizeof(int *));
    int *shiftAmt = malloc(sizeof(int *));

    // Switch to handle the different ways the operands are represented for
    // different functions.
    switch(ins->opMnemonic) {
        case TST :
        case TEQ :
        case CMP :
            // S is set for tst, teq and cmp instructions
            ins->setS = 1;
            // op1 and op2 specify registers Rn and Rm respectively.
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rn);
            sscanf(strtok(assIns->op2, REG_DELIMITER), "%i", Rm);
            break;
        case MOV :
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rd);
            if(assIns->op2[0] == '#') {
                // MOV currently doesn't work for constants > 0xFF
                ins->setI = 1;
                sscanf(strtok(assIns->op2, CONST_DELIMITER), "%i", immVal);
            } else if(assIns->op2 == 'r'){
                sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rm);
            }
            // Not sure if this is required or not
            //else {
            //    printf("Badly formed instruction");
            // }
            break;
        case LSL :
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rn);
            sscanf(strtok(assIns->op2, CONST_DELIMITER), "%i", shiftAmt);
        default:
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rd);
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rn);
            sscanf(strtok(assIns->op1, REG_DELIMITER), "%i", Rm);
            break;
    }

    // Assign values from the pointers assigned to in the above switch().
    ins->Rn = Rn;
    ins->Rm = Rm;
    ins->Rd = Rd;
    ins->immVal = immVal;
}

void getFormMult(instr_t *ins, assIns_t assIns) {
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

void getFormDatTran(instr_t *ins, assIns_t assIns) {

}

void getFormBranch(instr_t *ins, assIns_t assIns) {

}
