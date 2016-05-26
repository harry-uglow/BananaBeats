#include "getFormat.h"
#include "defs.h"
#include <stdint.h>

// Function intended to fill the necessary formatting fields in
// struct Instruction to aid encoding.
instr_t getFormat(assInstr_t *ins) {
    mnemonic_t mnemonic = mnemonicStringToEnum(ins->mnemonic);

}

mnemonic_t mnemonicStringToEnum(char mnemonic[]) {
    return ADD;
}
  /*For this function I intend to have an ordered table mapping
    a mnemonic's string representation to its mnemonic_t enum representation.
    For example map "add" to ADD. Then this function simply has to iterate
    through the key's of this table using strcmp until it either finds the key
    being looked for or goes past it. If the string is found, return the
    mapping, else throw an invalid assembly instruction error.
  */