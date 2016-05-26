#ifndef ARM11_19_DEFS_H
#define ARM11_19_DEFS_H

#include <stdint.h>
#include <stdlib.h>

// CONSTANTS
#define MEM_SIZE 65536
#define WORD_LENGTH 4
#define OFFSET 4
#define REG_PC 15
#define REG_CPSR 16
#define NUMBER_OF_REGISTERS 17


// INSTRUCTION TYPES
typedef enum executeType {
    DATA_PROCESS,
    MULTIPLY,
    DATA_TRANSFER,
    BRANCH,
    HALT
} exec_t;


// INSTRUCTION FORMAT BITS
typedef struct Instruction {
    int cond;
    int setI;
    int setP;
    int setU;
    int setA;
    int setS;
    int setL;
    int isRsShift;
    int opCode;
    int shiftType;
    int shiftAmount;
    int Rn;
    int Rd;
    int Rs;
    int Rm;
    int32_t offset;
    int32_t op2;
    exec_t type;

} instr_t;


// STATE OF PROCESSOR
typedef struct ARM {
    int8_t *memory;
    int32_t registers[NUMBER_OF_REGISTERS];
    instr_t *instruction;
    int32_t fetched;
	int isFetched;
	int isDecoded;
} arm_t;

#endif //ARM11_19_DEFS_H
