#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "defs.h"


// Function to execute the data processing instruction providing cond is valid
void executeDPI(arm_t *state) {
    instr_t *instr = state->instruction;
    int32_t operand1 = state->registers[instr->Rn];
    int32_t operand2 = instr->op2;
    switch (opCode) {
        case 0: // AND
            *rd = (operand1 & operand2);
            break;

        case 1: // EOR
            *rd = (operand1 ^ operand2);
            break;

        case 2: // Subtract
            *rd = (operand1 - operand2);
            break;

        case 3: // Subtract (op2 - rn)
            *rd = (operand2 - operand1);
            break;

        case 4: // Addition
            *rd = (operand1 + operand2);
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
            *rd = (operand1 | operand2);
            break;

        case 13: // Move
            *rd = operand2;
            break;
    }
}

bool condOk(void) {
    bool isOk = false;
    if (cond == 0 || cond == 1) {
        isOk = true;
    } else if (cond >= 10 && cond <= 14) {
        isOk = true;
    }

    return isOk;
}

int main(void) {
    int instruction = 0;
    if (condOk) {
        executeDPI;
    }
    return 1;
}


// NEED TO ADD THE FUNCTIONALITY TO UPDATE THE CSPR REGISTER
