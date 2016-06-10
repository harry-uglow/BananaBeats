#ifndef ARM11_19_DEFS_H
#define ARM11_19_DEFS_H

#include <stdint.h>
#include <stdlib.h>

// Constants
#define MEM_SIZE 65536
#define WORD_LENGTH 4
#define BIT_WORD_LENGTH 32
#define PC_OFFSET 8
#define REG_PC 15
#define REG_CPSR 16
#define NUMBER_OF_REGISTERS 17
#define BYTE 8
#define PRINT_LIMIT -1000000000
#define TRUE 1
 
// Useful bit numbers
#define C_BIT            29
#define CPSR_LAST        28
#define COND_LAST        28
#define OPCODE_LAST      21
#define RN_LAST          16
#define RD_LAST          12
#define RS_LAST           8
#define SHIFT_T_LAST      5
#define ROT_AMT_LAST      8
#define SHIFT_CONST_LAST  7
#define SHIFT_BYTE_3     24
#define SHIFT_BYTE_2      8
#define SHIFT_BYTE_1      8
#define SHIFT_BYTE_0     24
#define BRANCH_SHIFT      2
         
// Mask macros for decode()
#define MASK_I_BIT         0x02000000
#define MASK_P_BIT         0x01000000
#define MASK_U_BIT         0x00800000
#define MASK_A_BIT         0x00200000
#define MASK_S_BIT         0x00100000
#define MASK_RS_SHIFT_BIT  0x00000010
#define MASK_BRANCH        0x08000000
#define MASK_SDT           0x04000000
#define MASK_SIGN_EX       0xFC000000
#define MASK_COND          0xF0000000
#define MASK_NZCV          0xF0000000
#define MASK_MULT_DATA     0x020000F0
#define MASK_OPCODE        0x01E00000
#define MASK_OFF_BRCH      0x00FFFFFF
#define MASK_RN            0x000F0000
#define MASK_RD            0x0000F000
#define MASK_OFF_DATA      0x00000FFF
#define MASK_SHFT_CONST    0x00000F80
#define MASK_RS            0x00000F00
#define MASK_ROTATE        0x00000F00
#define MASK_END_BYTE      0x000000FF
#define MASK_SHIFT_T       0x00000060
#define MASK_RM            0x0000000F
#define MULT_ID            0x00000090

// Mask macros for executeInstructions.c
#define MASK_CARRY_BIT     0x100000000
#define MASK_Z_BIT         0x40000000
#define MASK_N_BIT         0x80000000
#define MASK_ALL_BUT_Z     0xBFFFFFFF

// Mask macros for utils.c
#define MASK_BYTE_3        0x000000FF
#define MASK_BYTE_2        0x0000FF00
#define MASK_BYTE_1        0x00FF0000
#define MASK_BYTE_0        0xFF000000

// NZCV bits for utils.c
#define Z_BIT              0x4
#define N_EQUALS_V_BITS    0x9
#define V_BIT              0x1
#define N_BIT              0x8

// Macros for isGPIOAddress
#define GPIO_0_TO_9        0x20200000
#define GPIO_10_TO_19      0x20200004
#define GPIO_20_TO_29      0x20200008
#define PIN_ON             0x2020001C
#define PIN_OFF            0x20200028

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
