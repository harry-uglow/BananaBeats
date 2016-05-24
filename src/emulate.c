#include "pipeline.c"
#include "emulate.h"


int main(int argc, char **argv) {
	
	arm_t arm;

    if (!initialiseProcessor(&arm)) {
        return EXIT_FAILURE;
    }

    if (!readFile(&arm, argv)) {
        return EXIT_FAILURE;
    }

	// Main loop for fetch-decode-execute cycle
	while(iteratePipeline(&arm)) {
		continue;
	}

	printFinalState(&arm);

	if(arm.memory != NULL) {
		free(arm.memory);
	}  

	return EXIT_SUCCESS;

}

int iteratePipeline(arm_t *state) {
	if(state->isDecoded) {
	    if(state->instruction->type == HALT) {
			return 0;
		}
		execute(state);
	}

	if(state->isFetched) {
		decode(state);
	}
	fetch(state);
	return 1;
}


