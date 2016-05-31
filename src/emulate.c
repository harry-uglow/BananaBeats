#include "emulator/pipeline.h"

int main(int argc, char **argv) {
	arm_t arm;

    // Initialise the processor by assigning space for registers and
	// memory on the heap and initialise everything to zero as required
    if(!initialiseProcessor(&arm)) {
        return EXIT_FAILURE;
    }

    // Read the input file and load it into memory
    if(!readFile(&arm, argv)) {
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
