#ifndef ARM11_19_ASSEMBLER_DEFS_H
#define ARM11_19_ASSEMBLER_DEFS_H

#include <stdint.h>
#include <stdlib.h>

// Constants
#define MEM_SIZE 65536
#define WORD_LENGTH 4
#define OFFSET 4
#define REG_PC 15
#define REG_CPSR 16
#define NUMBER_OF_REGISTERS 17

// Structure of assembly instruction
typedef struct assInstr {
	char mnemonic[];
	char op1[];
	char op2[];
	char op3[];
	char op4[];
} assIns_t;

// Structure of type of instructions
typedef enum executeType {
    DATA_PROCESS,
    MULTIPLY,
    DATA_TRANSFER,
    BRANCH,
    HALT
} exec_t;

// Mnemonic enum mapping instructions codes to numbers
typedef enum mnemonic {
    ADD,
    SUB,
    RSB,
    AND,
    EOR,
    ORR,
    MOV,
    TST,
    TEQ,
    CMP,
    MUL,
    MLA,
    LDR,
    STR,
    BEQ,
    BNE,
    BGE,
    BLT,
    BGT,
    BLE,
    B,
    LSL,
    ANDEQ
} mnemonic_t;

// Structure of instruction format
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

#endif //ARM11_19_ASSEMBELER_DEFS_H




