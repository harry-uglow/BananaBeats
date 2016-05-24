#include "utils.c"
#include "executeInstructions.h"


// Data Processing
void dataProcessing(arm_t *arm) {
    instr_t *instr = arm->instruction;
    int32_t operand1 = arm->registers[instr->Rn];
    int32_t operand2 = instr->op2;
    int opCode = instr->opCode;
    int32_t destReg = instr->Rd;

    switch (opCode) {
        case 0: // AND
            destReg = (operand1 & operand2);
            break;

        case 1: // EOR
            destReg = (operand1 ^ operand2);
            break;

        case 2: // Subtract
            destReg = (operand1 - operand2);
            break;

        case 3: // Subtract (op2 - rn)
            destReg = (operand2 - operand1);
            break;

        case 4: // Addition
            destReg = (operand1 + operand2);
            break;

        case 8: // AND but result not written (tst) ???
            (operand1 & operand2);
            break;

        case 9: // EOR but result not written (teq) ???
            (operand1 ^ operand2);
            break;

        case 10: // Cmp ???
            (operand1 - operand2);
            break;

        case 12: // OR (orr)
            destReg = (operand1 | operand2);
            break;

        case 13: // Move
            destReg = operand2;
            break;
    }


    // Update the CPSR register
    if (arm->instruction->setS) {
        
        // Z bit set if result is all zeros
        if ((0x00000000 | destReg) == 0x00000000) {
            arm->registers[REG_CPSR] |= 1 << 30;
        }

        // N bit set to bit 31 of the result
        int32_t nBit = destReg & 0x80000000;
        arm->registers[REG_CPSR] |= nBit;

    }
}

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
        arm->registers[REG_CPSR] |= 1 << 31; // Set bit 31 of CPSR register
    } else {
        arm->registers[REG_CPSR] &= ~(1 << 31); // Clear bit 31 of CPSR register
    }


}

void singleDataTransfer(arm_t *arm) {
    instr_t *ins = arm->instruction;

    int32_t offset = 0;
    if(ins->setI) {
        int32_t rmVal = arm->registers[ins->Rm];
        offset = executeShift(rmVal, ins->shiftType, ins->shiftAmount);
    } else {
        // Offset is an unsigned 12-bit immediate offset.
        int32_t offset = ins->offset;
    }
    uint32_t memAddr = arm->registers[ins->Rn];
    if(ins->setP) {
        // Pre-indexing mode
        if (ins->setU) {
            memAddr += offset;
        } else {
            memAddr -= offset;
        }
    }


    // Perform the load or store operation
    if(ins->setL) {
        arm->registers[ins->Rd] = arm->memory[memAddr];
    } else {
        arm->memory[memAddr] = arm->registers[ins->Rd];
    }

    if(!ins->setP) {
        // Post-indexing mode
        if(ins->setU) {
            arm->registers[ins->Rn] += offset;
        } else {
            arm->registers[ins->Rn] -= offset;
        }
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

	// Clear fetched and decoded parts of pipeline
	(arm->isFetched) = 0;
	(arm->isDecoded) = 0;    
}
