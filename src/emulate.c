#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {



	printf("Registers:\n");
	for(int i = 0; i < 13; i++) {
		printf("$%i  :          %d (0x%x)\n", i, arm->registers[i]); 
	}
	printf("PC  :          %d (0x%x)\n", arm->registers[15]);
	printf("CPSR:          %d (0x%x)\n", arm->registers[16]);
	printf("Non-zero memory:\n);

	int i = 0;

	while(arm->memory[i*4] != 0) {
		printf("0x%i: 0x%x\n", i*4, arm->memory[i*4]);
		i++;	
	}
	
  return EXIT_SUCCESS;
}
