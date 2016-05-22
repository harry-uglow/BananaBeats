#include "executeInstructions.h"
#include <stdio.h>


// Multiply instruction
void multiply(arm_t *arm) {
    int result;

    // Check condition is satisfied by CPSR register
    if (arm->instruction->cond != arm->registers[16]) {
        return;
    }

    // Rd = Rm * Rs
    result = arm->registers[arm->instruction->Rm] * arm->registers[arm->instruction->Rs];
    arm->registers[arm->instruction->Rd] = result;

    // Accumulate: Rd = Rm * Rs + Rn
    if (arm->instruction->setA) {
        arm->registers[arm->instruction->Rd] += arm->registers[arm->instruction->Rn];
    }

    // Consider bit 'S' and return if it isn't set
    if (!arm->instruction->setS) {
        return;
    }

    // Update CPSR register
    if (8000000 & result) {
        arm->registers[16] |= 1 << 31; // Set bit 31 of CPSR register
    } else {
        arm->registers[16] &= ~(1 << 31); // Clear bit 31 of CPSR register
    }


}



// Branch instruction 
void branch(arm_t *arm) {

	// (2's complement) 24 bit offset in branch instruction shifted left 2 bits & sign extended to 32 bits
    int32_t branchOffset = (arm->instruction->offset) << 2;

	// Offset is added to the PC register
    (arm->registers[15]) += branchOffset;

    // PC has changed and previously fetched instruction is no longer valid so the pipeline is cleared.
    (arm->fetched) = 0;
    
}
