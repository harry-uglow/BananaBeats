#include "getFormat.h"
#include "defs.h"
#include <stdint.h>

// Function intended to fill the necessary formatting fields in
// struct Instruction to aid encoding.
instr_t getFormat(assInstr_t *ins) {
    mnemonic_t mnemonic = mnemonicStringToEnum(ins->mnemonic);
    // Initialise instr_t for output later.
    instr_t out;
    setCond(out);
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
    if (ins->opMnemonic < MIN_BRANCH || B == ins->opMnemonic
        || LSL == ins->opMnemonic) {
        ins->cond = ALWAYS;
    } else {
        switch (ins->opMnemonic) {
            case BEQ :
            case ANDEQ:
                ins->cond = EQUAL;
                break;
            case BNE :
                ins->cond = NOT_EQUAL;
                break;
            case BGE :
                ins->cond = G_OR_EQ;
                break;
            case BLT :
                ins->cond = LESS_THAN;
                break;
            case BGT :
                ins->cond = GRTR_THAN;
                break;
            case BLE :
                ins->cond = L_OR_EQ;
                break;
            default:
                //error
                break;
        }
    }
}