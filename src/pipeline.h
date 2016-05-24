//
// Created by Harry on 21/05/2016.
//

#ifndef ARM11_19_PIPELINE_H
#define ARM11_19_PIPELINE_H

#include "defs.h"

void fetch(arm_t *state);
void decode(arm_t *state);
void execute(arm_t *state);

#endif //ARM11_19_PIPELINE_H
