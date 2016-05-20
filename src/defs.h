//
// Created by Harry on 20/05/2016.
//
/*
#ifndef ARM11_19_DEFS_H
#define ARM11_19_DEFS_H

#endif //ARM11_19_DEFS_H
*/
#define MEM_SIZE 65536
#define WORD_LENGTH 32
#define OFFSET 4

enum insType {
    DATA_PROCESS,
    MULTIPLY,
    DATA_TRANSFER,
    BRANCH
} ins_t;

typedef struct Instruction {
    int cond;
    int setI;
    int setP;
    int setU;
    int setA;
    int setS;
    int setL;
    int32_t Rn;
    int32_t Rd;
    int32_t Rs;
    int32_t Rm;
    int32_t offset;
    int32_t op2;
    enum insType type;

} instr_t;

typedef struct ARM {
    int8_t *memory;
    int32_t *registers;
    instr_t *instruction;
} arm_t;
