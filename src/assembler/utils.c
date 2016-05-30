#include "utils.h"
#include <stdio.h>
#include <memory.h>


int firstPass(assIns_t *instructions, char **argv, symbolTable_t *table, int *address) {
	// Open file to read from
	FILE *finput = fopen(argv[1],"r");
	
	// Check if assembly file cannot be opened
	if (finput == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 0;
	}

	char buffer[MAX_LINE_LENGTH];
	char *token;
	char *ops[4];

	// Some sort of loop construct before the code underneath
	fgets(buffer, MAX_LINE_LENGTH, finput);		
	token = strtok(buffer, TOK_DELIM);
	if(isLabel(token)) {
		symbolTable_put(token, address, table);
		if(strtok(NULL, TOK_DELIM) == NULL)  
	}
	
	
	for(int i = 0; i < 4; i++) {
		ops[i] = strtok(NULL, TOK_DELIM);		
	}
	
	
	// Finished reading input of assembly file
	fclose(finput);
	return 1;
}

int initialiseAssembler(assIns_t *instructions, symbolTable_t *table) {
	// Allocate memory onto the heap for an array of instructions
	instructions = calloc(MEM_SIZE, sizeof(assIns_t));
	
	// Check if memory allocation failed
	if(instructions == NULL) {
		printf("Memory could not be allocated onto the heap.\n");
		return 0;
	}	

	// Create new symbol table
	table = SymbolTable_new();
	return 1;
}

int writeToBinaryFile(int8_t *binInstructions, char **argv) {
	// Open file to write to
	FILE *foutput = fopen(argv[2], "wb");

	// Check if file cannot be opened
	if(foutput == NULL) {
		printf("Could not open file %s\n", argv[2]);
		return 0;
	}
	
	// Write all of the binary instructions encoded into the output file
	int pos = 0;
	while(TRUE) {
		int out = fwrite(&binInstructions[pos], sizeof(int8_t), 1, foutput);
		if(out != 1) {
			break;
		}
		pos++;
	}

	// Finished writing to output of binary file
	fclose(foutput); 
	return 1;
}

int isLabel(char *token) {
	// Check if token is label and remove colon
	if(token[strlen(token) - 1] == ':') {
		token[strlen(token) - 1] = '\0';
		return 1;
	}
	return 0;
}

int8_t *secondPass(assIns_t *instructions) {
	int8_t *memory = calloc(MEM_SIZE, sizeof(int8_t));
	for(int i = 0; i < (sizeof(*instructions) / sizeof(instructions[0])); i++) {
		int32_t instruction = encode(&instructions[i]);
		memory[WORD_LENGTH * i] = (int8_t)(MASK_BYTE_0 & instruction);
        memory[(WORD_LENGTH * i) + 1] = (int8_t)(MASK_BYTE_1 & instruction);
        memory[(WORD_LENGTH * i) + 2] = (int8_t)(MASK_BYTE_2 & instruction);
        memory[(WORD_LENGTH * i) + 3] = (int8_t)(MASK_BYTE_3 & instruction);
	}
    return memory;
}

void removeNewline(char *token) {
	token[strlen(token) - 1] = '\0';
}
