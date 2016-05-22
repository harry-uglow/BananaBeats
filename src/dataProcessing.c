#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

enum insType {
        DATA_PROCESS,
        MULTIPLY,
        DATA_TRANSFER,
        BRANCH
};

struct ARM {
        int8_t *memory;
        int32_t *registers;
        struct Instruction *instruction;
};

struct Instruction {
        int cond;
        int setI;
        int setP;
        int setU;
        int setA;
        int setS;
        int setL;
        int opCode;     // <----- added opCode
        int32_t Rn;
        int32_t Rd;
        int32_t Rs;
        int32_t Rm;
        int32_t offset;
        int32_t op2;
        enum insType type;

} ;



// Function to calculate operand2
int32_t getOperand2(arm_t *state) {

    if (setI) {

        // Zero-extend to 32 bits
        int32_t immConst = (0x000000FF & op2);
        // Calculate the rotation
        int rotation = 2 * ((0xF00 & op2) >> 8);

        // Bitwise rotate right by 'rotation'
        int32_t rotatedInt = (immConst >> rotation) | (immConst << (32 - rotation));

        return rotatedInt;

    } else {
        // The code in these brackets has been temporarily duplicated in
        // pipeline.c. I will resolve this. -HARRY 22/05/16 15:24

        // Get register Rm
        int rm = (0xF & op2);
        // Get shift value
        int shift = ((0xFF0 & op2) >> 4);
        // Get shift type
        int shiftType = ((0x06 & shift) >> 1);

        // get value of int in rm
        int32_t rmVal = state->registers[rm];

        int32_t shiftedVal = 0;

        // Check if bit 4 is == 1 or == 0
        if (0x1 & shift) {
            int rs = (0xF0 & shift) >> 4;
            int rsVal = state->registers[rs];
            int amount = (0xFF & rsVal);
            shiftedVal = executeShift(rmVal, shiftType,  amount);
        } else {
            int amount = (0xF8 & shift) >> 3;
            shiftedVal = executeShift(rmVal, shiftType, amount);
        }
    }
    return shiftedVal;
}


// Function to execute the data processing instruction providing cond is valid
void executeDPI(void) {
    int32_t operand1 = *rn;
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
