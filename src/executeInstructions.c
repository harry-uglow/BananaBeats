#include "utils.c"
#include "executeInstructions.h"


void dataProcessing(arm_t *arm) {
    // get value of Rm / execute shift (shiftType, shiftAmount)
    instr_t *instr = arm->instruction;
    int32_t operand1 = arm->registers[instr->Rn];
    int setI = instr->setI;
    int opCode = instr->opCode;
    int32_t destReg = instr->Rd;
    int32_t temp = 0;

    // Calculate operand2
    int32_t operand2;
    int carry = 0;
    if (setI) {
        operand2 = instr->op2;
    } else {
        int32_t rmVal = arm->registers[instr->Rm];
        int type = instr->shiftType;
        int amount = instr->shiftAmount;
        int32_t bitToCarry = 0;
        // switch on shift type here
        switch(type) {
            case 0:
                bitToCarry = 2 ^ (32 - (amount - 1));
                carry = (rmVal & bitToCarry) >> (amount - 1);
                break;

            case 1:
                bitToCarry = 2 ^ (amount - 1);
                carry = (rmVal & bitToCarry) >> (amount - 1);
                break;

            case 2: 
                bitToCarry = 2 ^ (amount - 1);
                carry = (rmVal & bitToCarry) >> (amount - 1);
                break;

            // Case for rotate is unnecessary as rotation has no carry
        }
        operand2 = executeShift(rmVal, type, amount);
    }
    int64_t op1_64 = operand1;
    int64_t op2_64 = operand2;

    switch (opCode) {
        case 0: // AND
            arm->registers[destReg] = (operand1 & operand2);
            temp = destReg;
            break;

        case 1: // EOR
            arm->registers[destReg] = (operand1 ^ operand2);
            temp = destReg;
            break;

        case 2: // Subtract
            arm->registers[destReg] = (operand1 - operand2);
            temp = destReg;
            carry = (0x0000000100000000 & (op1_64 - op2_64)) >> 32;
            carry = !carry;

            break;

        case 3: // Subtract (op2 - rn)
            arm->registers[destReg] = (operand2 - operand1);
            temp = destReg;
            carry = (0x0000000100000000 & (op1_64 - op2_64)) >> 32;
            carry = !carry;
            break;

        case 4: // Addition
            arm->registers[destReg] = (operand1 + operand2);
            temp = destReg;
            carry = (0x0000000100000000 & (op1_64 + op2_64)) >> 32;
            break;

        case 8: // AND but result not written (tst)
            temp = (operand1 & operand2);
            break;

        case 9: // EOR but result not written (teq)
            temp = (operand1 ^ operand2);
            break;

        case 10: // Cmp
            temp = (operand1 - operand2);
            carry = (0x0000000100000000 & (op1_64 - op2_64)) >> 32;
            carry = !carry;
            break;
            
        case 12: // OR (orr)
            arm->registers[destReg] = (operand1 | operand2);
            temp = destReg;
            break;

        case 13: // Move
            arm->registers[destReg] = operand2;
            temp = destReg;
            break;
    }


    // Update the CPSR register
    if (arm->instruction->setS) {
      
        // C bit is set depending on the carry out
        int32_t cBit = carry << 29;
        arm->registers[REG_CPSR] |= cBit;
        
        // Z bit set if result is all zeros
        if ((0x00000000 | temp) == 0x00000000) {
            arm->registers[REG_CPSR] |= (1 << 30);
        } else {
            arm->registers[REG_CPSR] &= 0xBFFFFFFF;
        }

        // N bit set to bit 31 of the result
        int32_t nBit = temp & 0x80000000;
        arm->registers[REG_CPSR] |= nBit;

    }
}


void multiply(arm_t *arm) {
    int result;

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
        offset = ins->offset;
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

    // Only perform valid memory accesses
    if(memAddr > MEM_SIZE) {
        printf("Error: Out of bounds memory access at address 0x%08x\n",
               memAddr);
    } else {
        // Perform the load or store operation
        if (ins->setL) {
            if((memAddr % WORD_LENGTH) != 0) {
                int32_t byte0 = arm->memory[memAddr] & 0x000000FF;
                int32_t byte1 = (arm->memory[memAddr + 1] & 0x000000FF) << 8;
                int32_t byte2 = (arm->memory[memAddr + 2] & 0x000000FF) << 16;
                int32_t byte3 = (arm->memory[memAddr + 3] & 0x000000FF) << 24;
                arm->registers[ins->Rd] = byte3 | byte2 | byte1 | byte0;
            } else {
                int32_t *wordSizedMem = (int32_t *) arm->memory;
                arm->registers[ins->Rd] = wordSizedMem[memAddr / WORD_LENGTH];
            }
        } else {
            arm->memory[memAddr] = arm->registers[ins->Rd];
        }
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


 
void branch(arm_t *arm) {
	// (2's complement) 24 bit offset in branch instruction shifted left 2 bits & sign extended to 32 bits
    int32_t branchOffset = (arm->instruction->offset) << 2;
    int32_t topBit = (0x02000000 & branchOffset);
    int32_t signExtendBits = topBit ? 0xFC000000 : 0;
    branchOffset |= signExtendBits;

	// Offset is added to the PC register
    (arm->registers[15]) += branchOffset;

    // PC has changed and previously fetched instruction is no longer valid so the pipeline is cleared.
    (arm->fetched) = 0;

	// Clear fetched and decoded parts of pipeline
	(arm->isFetched) = 0;
	(arm->isDecoded) = 0;    
}
