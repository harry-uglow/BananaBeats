#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "defs.h"


// Function to execute the data processing instruction providing cond is valid

void executeDPI(arm_t *arm) {
    instr_t *instr = arm->instruction;
    int32_t operand1 = arm->registers[instr->Rn];
    int32_t operand2 = instr->op2;
    int opCode = instr->opCode;
    int32_t destReg = instr->Rd;

    switch (opCode) {
        case 0: // AND
            destReg = (operand1 & operand2);
            break;

        case 1: // EOR
            destReg = (operand1 ^ operand2);
            break;

        case 2: // Subtract
            destReg = (operand1 - operand2);
            break;

        case 3: // Subtract (op2 - rn)
            destReg = (operand2 - operand1);
            break;

        case 4: // Addition
            destReg = (operand1 + operand2);
            break;

        case 8: // AND but result not written (tst) ???
            (operand1 & operand2);
            break;

        case 9: // EOR but result not written (teq) ???
            (operand1 ^ operand2);
            break;

        case 10: // Cmp ???
            (operand1 - operand2);
            break;

        case 12: // OR (orr)
            destReg = (operand1 | operand2);
            break;

        case 13: // Move
            destReg = operand2;
            break;
    }


    // Update the CPSR register
    if (arm->instruction->setS) {
        
        // Z bit set if result is all zeros
        if ((0x00000000 | destReg) == 0x00000000) {
            arm->registers[REG_CPSR] |= 1 << 30;
        }

        // N bit set to bit 31 of the result
        int32_t nBit = destReg & 0x80000000;
        arm->registers[REG_CPSR] |= nBit;


    }

}


// NEED TO ADD THE FUNCTIONALITY TO UPDATE THE CSPR REGISTER
