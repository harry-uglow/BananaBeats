#ifndef ARM11_19_PIPELINE_H
#define ARM11_19_PIPELINE_H

void fetch(arm_t *state);
void decode(arm_t *state);
void execute(arm_t *state);

#endif //ARM11_19_PIPELINE_H
