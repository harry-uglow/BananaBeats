#include <stdio.h>
#include "defs.h"
#include "utils.h"


#define TRUE 1

int32_t executeShift(int32_t value, int shiftType, int amount) {
    int32_t shiftedValue = 0;

    switch (shiftType) {
        // logical shift left
        case 0:
            shiftedValue = value << amount;
            break;

            // logical shift right
        case 1:
            shiftedValue = (int)((unsigned int) value >> amount);
            break;

            // arithmetic shift right
        case 2:
            shiftedValue = value >> amount;
            break;

            // rotate right
        case 3:
            shiftedValue = (value >> amount) | (value << (32 - amount));
            break;

    }
    return shiftedValue;
}

int checkCond(int cond, int NZCV){
    int passesCond = 0;
    switch (cond){
        case 0 :
            // Equal
            passesCond = 0x4 & NZCV;
            break;
        case 1 :
            // Not equal
            passesCond = !(0x4 & NZCV);
            break;
        case 10 :
            // Greater or equal
            passesCond = ((9 == (0x9 & NZCV)) || !(0x9 & NZCV));
            break;
        case 11 :
            // Less than
            passesCond = ((1 == (0x9 & NZCV)) || (8 == (0x9 & NZCV)));
            break;
        case 12 :
            // Greater than
            passesCond = (!(0x4 & NZCV) &&
                          ((9 == (0x9 & NZCV)) || !(0x9 & NZCV)));
            break;
        case 13 :
            // Less than or equal
            passesCond = ((0x4 & NZCV) ||
                          ((1 == (0x9 & NZCV)) || (8 == (0x9 & NZCV))));
            break;
        case 14 :
            // Always
            passesCond = 1;
            break;
    }
    return passesCond;
}


int32_t reverseByteOrder(int32_t n) {
    // Little-endian means retrieving multiple bytes from the memory in one go
    // will retrieve them in the wrong byte order. This function reverses
    // byte order.
    int32_t byte3 = (0x000000FF & n) << 24;
    int32_t byte2 = (0x0000FF00 & n) << 8;
    int32_t byte1 = (0x00FF0000 & n) >> 8;
    int32_t byte0 = (0xFF000000 & n) >> 24;
    return (byte3 | byte2 | byte1 | byte0);
}


void printFinalState(arm_t *state) {

    printf("Registers:\n");

    int pc   = state->registers[REG_PC];
    int cpsr = state->registers[REG_CPSR];

    // Print out contents of registers 0-9
    for(int i = 0; i < 10; i++) {
        printf("$%i  :%12d (0x%08x)\n", i, state->registers[i], state->registers[i]);
    }

    // Print out contents of registers 10-12
    for(int j = 10; j < 13; j++) {
        printf("$%i :%12d (0x%08x)\n", j, state->registers[j], state->registers[j]);
    }

    // Print out contents of PC and CPSR
    printf("PC  :%12d (0x%08x)\n", pc, pc);
    printf("CPSR:%12d (0x%08x)\n", cpsr, cpsr);

    // Print out non-zero contents of memory
    printf("Non-zero memory:\n");

    int k = 0;

    int8_t tmp = state->memory[5];

    int32_t *wordSizedMem = (int32_t *)state->memory;

    while(wordSizedMem[k] != 0) {
        printf("0x%08x: 0x%08x\n", k * WORD_LENGTH,
               (reverseByteOrder(wordSizedMem[k])));
        k++;
    }

}

int readFile(arm_t *state, char **argv) {

        // Reading file input
        FILE *finput = fopen(argv[1],"rb");

        if(finput == NULL) {
            printf("Could not open %s", argv[1]);
            return 0;
        }

        // Loop to read binary file, one byte at a time,
        // and copy the bytes into processor's memory until
        // there are no more bytes left to read in the file
        int8_t byteInput; // Temporary byte variable to store read byte on each iteration of the loop
        int8_t *pByteInput = &byteInput;
        int memPos = 0;
        while(TRUE) {
                int in = fread(pByteInput,sizeof(int8_t),1,finput);
                if(in != 1) {
                        break;
                }
                state->memory[memPos] = byteInput;
                memPos++;
        }
        fclose(finput);
        // Finished reading file input

    return 1;

}

int initialiseProcessor(arm_t *state) {

    // Assign memory array onto heap
    state->memory = (int8_t*)calloc(MEM_SIZE, sizeof(int8_t));

    if (state->memory == NULL) {
        printf("Failed to create memory array on heap");
        return 0;
    }
    for (int i = 0; i < NUMBER_OF_REGISTERS; ++i) {
        state->registers[i] = 0;
    }
    state->isDecoded = 0;
    state->isFetched = 0;
    state->instruction = (instr_t *) calloc(1, sizeof(instr_t));
    return 1;
}
