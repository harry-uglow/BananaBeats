#include "utils.h"

int32_t executeShift(int32_t value, int shiftType, int amount) {
    int32_t shiftedValue = 0;
    switch(shiftType) {
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
        default:
            printf("Error. executeShift() called with invalid shiftType");
            break;
    }
    return shiftedValue;
}

int checkCond(int cond, int NZCV){
    int passesCond = 0;
    switch(cond){
        // Equal
        case 0 :
            passesCond = Z_BIT & NZCV;
            break;
        // Not equal
        case 1 :
            passesCond = !(Z_BIT & NZCV);
            break;
        // Greater or equal
        case 10 :
            passesCond = ((N_EQUALS_V_BITS == (N_EQUALS_V_BITS & NZCV)) ||
                                               !(N_EQUALS_V_BITS & NZCV));
            break;
        // Less than
        case 11 :
            passesCond = ((V_BIT == (N_EQUALS_V_BITS & NZCV)) ||
                                     (N_BIT == (N_EQUALS_V_BITS & NZCV)));
            break;
        // Greater than
        case 12 :
            passesCond = (!(Z_BIT & NZCV) &&
                          ((N_EQUALS_V_BITS == (N_EQUALS_V_BITS & NZCV)) || 
                                               !(N_EQUALS_V_BITS & NZCV)));
            break;
        // Less than or equal
        case 13 :
            passesCond = ((Z_BIT & NZCV) ||
                          ((V_BIT == (N_EQUALS_V_BITS & NZCV)) ||
                           (N_BIT == (N_EQUALS_V_BITS & NZCV))));
            break;
        // Always
        case 14 :
            passesCond = 1;
            break;
        default:
            printf("Error. checkCond() called with invalid condition.");
            break;
    }
    return passesCond;
}

int32_t reverseByteOrder(int32_t n) {
    // This function reverses the byte order of the retrieved bytes 
    // from memory since they are in little endian format.
    int32_t byte3 = (MASK_BYTE_3 & n) << SHIFT_BYTE_3;
    int32_t byte2 = (MASK_BYTE_2 & n) << SHIFT_BYTE_2;
    int32_t byte1 = (MASK_BYTE_1 & n) >> SHIFT_BYTE_1;
    int32_t byte0 = (MASK_BYTE_0 & n) >> SHIFT_BYTE_0;
    return (byte3 | byte2 | byte1 | byte0);
}

void printFinalState(arm_t *state) {
    printf("Registers:\n");
    
    // Contents of PC and CPSR are extracted 
    int pc   = state->registers[REG_PC];
    int cpsr = state->registers[REG_CPSR];

    // Print out contents of registers 0-9
    for(int i = 0; i < 10; i++) {
        if(state->registers[i] < 0 && state->registers[i] <= PRINT_LIMIT) {
            printf("$%i  :%12d (0x%08x)\n", i, state->registers[i],
               state->registers[i]);
        } else {
            printf("$%i  :%11d (0x%08x)\n", i, state->registers[i],
               state->registers[i]);
        }
    }

    // Print out contents of registers 10-12
    for(int j = 10; j < 13; j++) {
        if(state->registers[j] < 0 && state->registers[j] <= PRINT_LIMIT) {
            printf("$%i :%12d (0x%08x)\n", j, state->registers[j],
               state->registers[j]);
        } else {
            printf("$%i :%11d (0x%08x)\n", j, state->registers[j],
               state->registers[j]);
        }
    }

    // Print out contents of PC and CPSR
    if(pc < 0 && pc < PRINT_LIMIT) {
        printf("PC  :%12d (0x%08x)\n", pc, pc);
    } else {
        printf("PC  :%11d (0x%08x)\n", pc, pc);
    }
    
    if(cpsr < 0 && cpsr < PRINT_LIMIT) {
        printf("CPSR:%12d (0x%08x)\n", cpsr, cpsr);
    } else {
        printf("CPSR:%11d (0x%08x)\n", cpsr, cpsr);
    }
    
    // Print out non-zero contents of memory
    printf("Non-zero memory:\n");

    int32_t *wordSizedMem = (int32_t *)state->memory;
    
    // Traverse through memory array & print out non-zero contents
    for(int k = 0; k < MEM_SIZE / WORD_LENGTH; k++) {
        if (wordSizedMem[k] != 0) {
            printf("0x%08x: 0x%08x\n", k * WORD_LENGTH,
                   (reverseByteOrder(wordSizedMem[k])));
        }
    }
}

int readFile(arm_t *state, char **argv) {
    // Open file input to read from
    FILE *finput = fopen(argv[1],"rb");

    // Check if file cannot be opened
    if(finput == NULL) {
        printf("Could not open %s\n", argv[1]);
        return 0;
    }

    // Loop to read binary file, one byte at a time, and copy the
    // bytes into processor's memory until there are no more
    // bytes left to read in the file. byteInput is a temporary
    // variable to store the byte that's read on each iteration of the loop.
    int8_t byteInput;
    int8_t *pByteInput = &byteInput;
    int memPos = 0;
    while(TRUE) {
        int in = (int) fread(pByteInput, sizeof(int8_t), 1, finput);
        if(in != 1) {
            break;
        }
        state->memory[memPos] = byteInput;
        memPos++;
    }

    // Finished reading file input
    fclose(finput);
    return 1;
}

int initialiseProcessor(arm_t *state) {
    // Assign memory array onto heap
    state->memory = (int8_t *) calloc(MEM_SIZE, sizeof(int8_t));
    
    // Check for failure of memory allocation
    if (state->memory == NULL) {
        printf("Failed to create memory array on heap\n");
        return 0;
    }
    
    // Initialise all registers to 0
    for (int i = 0; i < NUMBER_OF_REGISTERS; ++i) {
        state->registers[i] = 0;
    }
    
    // Initialise pipeline's fetched & decoded instructions to 0
    state->isDecoded = 0;
    state->isFetched = 0;
    
    // Allocate memory onto the heap for the instruction bits 
    // and initialise all bits to 1
    state->instruction = (instr_t *) calloc(1, sizeof(instr_t));
    return 1;
}
