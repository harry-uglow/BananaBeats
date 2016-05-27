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

typedef enum OpCodes {
	AND,
	EOR,
	SUB,
	RSB,
	ADD,
	TST = 8,
	TEQ = 9,
	CMP = 10,
	ORR = 12,
	MOV = 13
} opCode_t;

// Constants arising from mnemonic_t
#define MAX_DATA_PROCESS 9
#define MIN_MULTIPLY 10
#define MAX_MULTIPLY 11
#define MIN_DATA_TRANSFER 12
#define MAX_DATA_TRANSFER 13
#define MIN_BRANCH 14
#define MAX_BRANCH 20
#define MIN_SPECIAL 21

typedef enum Cond {
	EQUAL,
	NOT_EQUAL,
	G_OR_EQ = 10,
	LESS_THAN = 11,
	GRTR_THAN = 12,
	L_OR_EQ = 13,
	ALWAYS = 14,
};

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
    int shiftType;
	int shiftAmount;
	int Rn;
	int Rd;
	int Rs;
	int Rm;
	opCode_t opCode;
	int32_t offset;
    int32_t op2;
    exec_t type;
	mnemonic_t opMnemonic;
} instr_t;

#endif //ARM11_19_ASSEMBELER_DEFS_H




