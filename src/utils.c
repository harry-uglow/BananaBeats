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


void printFinalState(arm_t *state) {

        printf("Registers:\n");

        int pc   = state->registers[REG_PC];
        int cpsr = state->registers[REG_CPSR];

        // Print out contents of registers 0-9
        for(int i = 0; i < 10; i++) {
            printf("$%i  :%12d (0x%08x)\n", i, state->registers[i], state->registers[i]);
        }

        // Print out contents of registers 10-12
        for(int j = 0; j < 13; j++) {
            printf("$%i :%12d (0x%08x)\n", j, state->registers[j], state->registers[j]);
        }

        // Print out contents of PC and CPSR
        printf("PC  :%12d (0x%08x)\n", pc, pc);
        printf("CPSR:%12d (0x%08x)\n", cpsr, cpsr);

        // Print out non-zero contents of memory
        printf("Non-zero memory:\n");

        int k = 0;

        while(state->memory[k*4] != 0) {
            printf("0x%08x: 0x%08x\n", k*4, (state->memory[k*4]));
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
    //int8_t *memory =
//    if (memory == NULL) {
//        printf("Failed to create memory array on heap");
//        return 0;
//    }

    // Assign registers array onto heap
     //int32_t *registers =


//    if (registers == NULL) {
//        printf("Failed to create registers array on heap");
//        return 0;
//    }

    // Point the arm state to register and memory arrays on the heap
    state->memory = (int8_t*)calloc(MEM_SIZE, sizeof(int8_t));
    for (int i = 0; i < NUMBER_OF_REGISTERS; ++i) {
        state->registers[i] = 0;
    }
    state->isDecoded = 0;
    state->isFetched = 0;

    return 1;
}

void removeArraysFromHeap(arm_t *state) {
    // Clear memory and register arrays
//    if (memory != NULL) {
//        free(memory);
//    }
//    if (registers != NULL) {
//        free(registers);
//    }
}
             
