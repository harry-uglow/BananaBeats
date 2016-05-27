#ifndef ARM11_19_ENCODEINSTRUCTIONS_H
#define ARM11_19_ENCODEINSTRUCTIONS_H

int32_t encodeDataProcessing(instr_t *instr);
int32_t encodeMultiply(instr_t *instr);
int32_t encodeSingleDataTransfer(instr_t *instr);
int32_t encodeBranch(instr_t *instr);
int32_t encode(instr_t *instr);

#endif //ARM11_19_ENCODEINSTRUCTIONS_H
