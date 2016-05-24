
#ifndef ARM11_19_DEFS_H
#define ARM11_19_DEFS_H

#include <stdint.h>
#define MEM_SIZE 65536
#define WORD_LENGTH 4
#define OFFSET 4
#define REG_PC 15
#define REG_CPSR 16
#define NUMBER_OF_REGISTERS 17


typedef enum insType {
    DATA_PROCESS,
    MULTIPLY,
    DATA_TRANSFER,
    BRANCH,
    HALT
} ins_t;

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
    int32_t Rn;
    int32_t Rd;
    int32_t Rs;
    int32_t Rm;
    int32_t offset;
    int32_t op2;
    ins_t type;

} instr_t;

typedef struct ARM {
    int8_t *memory;
    int32_t *registers;
    instr_t *instruction;
    int32_t fetched;
} arm_t;
#endif //ARM11_19_DEFS_H
