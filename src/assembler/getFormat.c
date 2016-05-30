#include "getFormat.h"
#include "defs.h"
#include "symbolTable.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

mnemonic_t mnemonicStringToEnum(char mnemonic[4]);
void setCond(instr_t *ins);
void getFormDatProc(instr_t *ins, assIns_t *assIns);
void getFormMult(instr_t *ins, assIns_t *assIns);
void getFormDatTran(instr_t *ins, assIns_t *assIns);
void getFormBranch(instr_t *ins, assIns_t *assIns);
int getIntFromString(char *str);

// Function intended to fill the necessary formatting fields in
// struct Instruction to aid encoding.
instr_t getFormat(assIns_t *assIns) {
    // Initialise instr_t for output later.
    instr_t out;
    out.opMnemonic = mnemonicStringToEnum(assIns->mnemonic);

    // Condition applies to all instruction types
    setCond(&out);

    if(out.opMnemonic <= MAX_DATA_PROCESS) {
        out.type = DATA_PROCESS;
        getFormDatProc(&out, assIns);
    } else if(out.opMnemonic <= MAX_MULTIPLY) {
        out.type = MULTIPLY;
        getFormMult(&out, assIns);
    } else if(out.opMnemonic <= MAX_DATA_TRANSFER) {
        out.type = DATA_TRANSFER;
        getFormDatTran(&out, assIns);
    } else if(out.opMnemonic <= MAX_BRANCH) {
        out.type = BRANCH;
        getFormBranch(&out, assIns);
    } else {
        out.type = HALT;
    }

    return out;
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
        ins->opMnemonic == CMP) {
        ins->setS = 1;
    }

    // Set up safely allocated pointers for use in sscanf
    int *Rn = malloc(sizeof(int *));
    int *Rd = malloc(sizeof(int *));
    int *Rm = malloc(sizeof(int *));

    // Switch to handle the different ways the operands are represented for
    // different functions.
    switch(ins->opMnemonic) {
        case CMP :
        case TEQ :
        case TST :

            // S is set for tst, teq and cmp instructions
            ins->setS = 1;
            // op1 and op2 specify registers Rn and Rm respectively.
            ins->Rn = getIntFromString(assIns->op1);
            ins->Rm = getIntFromString(assIns->op2);
            break;
        case MOV :
            ins->Rd = getIntFromString(assIns->op1);
            if(assIns->op2[0] == EXPR_SYMBOL) {
                // MOV currently doesn't work for constants > 0xFF
                ins->setI = 1;
                ins->immVal = getIntFromString(assIns->op2);
            } else if(assIns->op2[0] == REG_SYMBOL){
                ins->Rm = getIntFromString(assIns->op2);
            }
            // Not sure if this is required or not
            //else {
            //    printf("Badly formed instruction");
            //}
            break;
        case LSL :
            ins->Rn = getIntFromString(assIns->op1);
            ins->shiftAmount = getIntFromString(assIns->op2);
        default:
            ins->Rd = getIntFromString(assIns->op1);
            ins->Rn = getIntFromString(assIns->op2);
            ins->Rm = getIntFromString(assIns->op3);
            break;
    }

    // Assign values from the pointers assigned to in the above switch().
    ins->Rn = *Rn;
    ins->Rm = *Rm;
    ins->Rd = *Rd;
}

void getFormMult(instr_t *ins, assIns_t *assIns) {

    // Set A bit
    if (ins->opMnemonic == MUL) {
        ins->setA = 0;
    } else {
        ins->setA = 1;
    }
    // Set S bit
    ins->setS = 0;

    ins->Rd = getIntFromString(assIns->op1);
    ins->Rm = getIntFromString(assIns->op2);
    ins->Rs = getIntFromString(assIns->op3);
    ins->Rn  =getIntFromString(assIns->op4);

}

void getFormDatTran(instr_t *ins, assIns_t *assIns){
    // Unless otherwise specified, the P bit is set (pre-indexing mode)
    ins->setP = 1;
    // Rd always in op1 position
    ins->Rd = getIntFromString(assIns->op1);

    // If ldr instruction, then setL 1
    if(ins->opMnemonic == LDR) {
        ins->setL = 1;
        if(assIns->op2[0] == NUM_CONST_SYM) {
            // Op2 represents a numeric constant
            int32_t expression = getIntFromString(assIns->op2);
            if(expression <= MAX_MOV_LDR) {
                // If the expression value is small enough to be used in a mov,
                // change <=expression> to <#expression> and use mov instead
                assIns->op2[0] = EXPR_SYMBOL;
                assIns_t treatAsMov = {MOV_MNEMONIC, assIns->op1, assIns->op2};
                ins->opMnemonic = MOV;
                getFormDatProc(ins, &treatAsMov);
                return;
            }
            // encode() is expected to put the SDTExpression in four bytes at
            // the end of the program and then calculate the offset from the PC
            // to the address of this expression
            ins->SDTExpression = expression;
            ins->Rn = REG_PC;
        }
    } else {
        ins->setL = 0;
    }
    char part1[50];
    char part2[50];
    sscanf(strtok(assIns->op2, SDT_OP2_SPLIT), "%s%s", part1, part2);
    ins->Rn = getIntFromString(part1);
    ins->offset = getIntFromString(part2);
    if (strrchr(part1, ']')) {
        // Post-indexing
        ins->setP = 0;
    }
}
void getFormBranch(instr_t *ins, assIns_t *assIns) {

    // Branch may or may not be needed. I'll get back to this.
    char *expression = assIns->op1;
    if (isdigit(*expression)) {
        ins->targetAddress = (int16_t) assIns->op1;
    } else {
        ins->targetAddress = SymbolTable_get(expression, table); 
    }
}

int getIntFromString(char *str) {
    while(*str) {
        if(isdigit(*str)) {
            return atoi(str);
        } else {
            str++;
        }
    }
    return 0;
}

mnemonic_t mnemonicStringToEnum(char mnemonic[4]) {
    /*For this function I intend to have an ordered table mapping
      a mnemonic's string representation to its mnemonic_t enum representation.
      For example map "add" to ADD. Then this function simply has to iterate
      through the key's of this table using strcmp until it either finds the key
      being looked for or goes past it. If the string is found, return the
      mapping, else throw an invalid assembly instruction error.
    */
    // UPDATE: I hate this code, but any clever solution seems to be beyond
    // the scope of the short C course and will certainly take longer to work
    // out than we have time for on this course.
    if (!strcmp(mnemonic, "and")) {
        return AND;
    } else if (!strcmp(mnemonic, "eor")) {
        return EOR;
    } else if (!strcmp(mnemonic, "sub")) {
        return SUB;
    } else if (!strcmp(mnemonic, "rsb")) {
        return RSB;
    } else if (!strcmp(mnemonic, "add")) {
        return ADD;
    } else if (!strcmp(mnemonic, "tst")) {
        return TST;
    } else if (!strcmp(mnemonic, "cmp")) {
        return CMP;
    } else if (!strcmp(mnemonic, "teq")) {
        return TEQ;
    } else if (!strcmp(mnemonic, "orr")) {
        return ORR;
    } else if (!strcmp(mnemonic, "mov")) {
        return MOV;
    } else if (!strcmp(mnemonic, "lsl")) {
        return LSL;
    } else if (!strcmp(mnemonic, "mul")) {
        return MUL;
    } else if (!strcmp(mnemonic, "mla")) {
        return MLA;
    } else if (!strcmp(mnemonic, "ldr")) {
        return LDR;
    } else if (!strcmp(mnemonic, "str")) {
        return STR;
    } else if (!strcmp(mnemonic, "b")) {
        return B;
    } else if (!strcmp(mnemonic, "beq")) {
        return BEQ;
    } else if (!strcmp(mnemonic, "bne")) {
        return BNE;
    } else if (!strcmp(mnemonic, "bge")) {
        return BGE;
    } else if (!strcmp(mnemonic, "blt")) {
        return BLT;
    } else if (!strcmp(mnemonic, "bgt")) {
        return BGT;
    } else if (!strcmp(mnemonic, "ble")) {
        return BLE;
    } else if (!strcmp(mnemonic, "andeq")) {
        return ANDEQ;
    } else {
        printf("Invalid opcode mnemonic. Exiting program");
        exit(1);
    }
}
