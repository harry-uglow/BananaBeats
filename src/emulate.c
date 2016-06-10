#include "emulator/pipeline.h"

int main(int argc, char **argv) {
    // Create arm state
    arm_t arm;

    // Initialise the processor by allocating space for registers and
    // memory on the heap and initialise everything to zero as required
    if (!initialiseProcessor(&arm)) {
        return EXIT_FAILURE;
    }

    // Read the input file and load it into memory
    if (!readFile(&arm, argv)) {
        return EXIT_FAILURE;
    }

    // Execute main loop for fetch-decode-execute cycle
    while(iteratePipeline(&arm)) {
        continue;
    }

    // Print state information to standard output
    printFinalState(&arm);

    // Null check before clearing memory from heap
    if (arm.memory != NULL) {
        free(arm.memory);
    }  
    return EXIT_SUCCESS;
}
