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
#define MASK_BYTE_0 0x000000FF
#define MASK_BYTE_1 0x0000FF00
#define MASK_BYTE_2 0x00FF0000
#define MASK_BYTE_3 0xFF000000
#define REG_SYMBOL 'r'
#define EXPR_SYMBOL '#'
#define MAX_MOV_LDR 0xFF
#define SDT_OP2_SPLIT ","
#define MOV_MNEMONIC "mov"
#define NUM_CONST_SYM '='
#define TRUE 1

// Encode Bit Shift Amounts
#define COND_BITS 28
#define I_BIT 25
#define P_BIT 24
#define U_BIT 23
#define A_BIT 21
#define OPCODE_BITS 21
#define S_BIT 20
#define L_BIT 20
#define RN_BITS 16
#define RD_BITS 12
#define RS_BITS 8
#define IMMVAL_SHIFTAMOUNT_BITS 8
#define REG_SHIFTAMOUNT_BITS 3
#define SHIFT_RS_BITS 4
#define SHIFT_BITS 4
#define SHIFT_TYPE_BITS 1

// Encode Constant Bits
#define MULT_PREDEFINED_BITS 0x00000090
#define SDT_PREDEFINED_BITS 0x04000000
#define BRANCH_PREDEFINED_BITS 0x0C000000
#define HALT_PREDEFINED_INSTRUCTION 0x00000000

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
	AND,
	EOR,
	SUB,
	RSB,
	ADD,
	TST = 8,
	CMP = 9,
	TEQ = 10,
	ORR = 12,
	MOV = 13,
	LSL,
	MUL,
	MLA,
	LDR,
	STR,
	B,
	BEQ,
	BNE,
	BGE = 30,
	BLT = 31,
	BGT = 32,
	BLE = 33,
	ANDEQ
} mnemonic_t;

// Constants arising from mnemonic_t
#define MAX_DATA_PROCESS 14
#define MIN_MULTIPLY 15
#define MAX_MULTIPLY 16
#define MIN_DATA_TRANSFER 17
#define MAX_DATA_TRANSFER 18
#define MIN_BRANCH 19
#define MAX_BRANCH 25
#define BRANCH_OFFSET 20

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
	int opCode;
	int immVal;
	int32_t offset;
    int32_t op2;
    exec_t type;
	mnemonic_t opMnemonic;
	int32_t SDTExpression;
} instr_t;

#endif //ARM11_19_ASSEMBELER_DEFS_H




