#include "pipeline.c"
#include "emulate.h"

int main(int argc, char **argv) {
	arm_t arm;

    // Initialise the processor by assigning memory for registers and memory
    // and initlailise everything to zero as required
    if (!initialiseProcessor(&arm)) {
        return EXIT_FAILURE;
    }

    // Read the input file and load it into memory
    if (!readFile(&arm, argv)) {
        return EXIT_FAILURE;
    }

	// Main loop for fetch-decode-execute cycle
	while(iteratePipeline(&arm)) {
        continue;
	}

    // Send state information to standard output
	printFinalState(&arm);

    // Clear memory from heap
	if(arm.memory != NULL) {
		free(arm.memory);
	}  

	return EXIT_SUCCESS;
}

// One iteration of the pipeline cycle
int iteratePipeline(arm_t *state) {
    // Execute if the instruction has been decoded
	if(state->isDecoded) {
	    if(state->instruction->type == HALT) {
			return 0;
		}
		execute(state);
	}

    // Decode if the instruction has been fetched
	if(state->isFetched) {
		decode(state);
	}

    // Fetch the next instruction
	fetch(state);
	return 1;
}


