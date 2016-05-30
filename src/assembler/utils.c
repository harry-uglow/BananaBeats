#include "utils.h"
#include <stdio.h>
#include <memory.h>


int firstPass(assIns_t *instruction, char **argv) {
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
	char *rest;
	char *temp[4];
	int opSignal[4] = {0, 0, 0, 0};

	while(fgets(buffer, MAX_LINE_LENGTH, finput) != NULL) {		
		// Extract first token in string 
		token = strtok(buffer, TOK_DELIM);
		rest = strtok(NULL, "");
	
		// Check if first token is label	
		if(isLabel(token)) {
			SymbolTable_put(token, &address, &table);
		} else {
			strcpy(instruction[address].mnemonic, token);
		}
	
		// Parse through rest of the string & fill up array of operands
		for(int i = 0; i < 4; i++) {
			if(checkBrackets(rest, temp[i])) {
				ops[i] = strtok(rest, TOK_DELIM);
				opSignal[i] = 1;
				strcpy(buffer, rest);	
			} else {	
				ops[i] = strtok(NULL, TOK_DELIM);
			}		
		}
	
		char *strToken;
		// Set all non-null operands to compoents of assembly instructions
		if(ops[0] != NULL) {
			if(opSignal[0]) {
				strToken = temp[0];
			} else {
				strToken = ops[0];
			}
			strcpy(instruction[address].op1, strToken);
		}

		if(ops[1] != NULL) {
			if(opSignal[1]) {
				strToken = temp[1];
			} else {
				strToken = ops[1];
			}
			strcpy(instruction[address].op2, strToken);
		}
	
		if(ops[2] != NULL) {
			if(opSignal[2]) {
				strToken = temp[2];
			} else {
				strToken = ops[2];
			}
			strcpy(instruction[address].op3, strToken);
		}

		if(ops[3] != NULL) {
			if(opSignal[3]) {
				strToken = temp[3];
			} else {
				strToken = ops[3];
			}
			strcpy(instruction[address].op4, strToken);
		}	
		
		// Increment address
		address++;
	}
		
	// Finished reading input of assembly file
	fclose(finput);
	return 1;
}

int initialiseAssembler(assIns_t *instructions) {
	// Allocate memory onto the heap for an array of instructions
	instructions = calloc(MEM_SIZE, sizeof(assIns_t));
	
	// Check if memory allocation failed
	if(instructions == NULL) {
		printf("Memory could not be allocated onto the heap.\n");
		return 0;
	}	

	// Create new symbol table
	table = *SymbolTable_new();

	// Initialise address counter
	address = 0;
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
	for(int i = 0; i < address; i++) {
		fwrite(&binInstructions[i], sizeof(int8_t), 1, foutput);
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

void secondPass(assIns_t *instructions) {
	for(int i = 0; i < (sizeof(*instructions) / sizeof(instructions[0])); i++) {
		int32_t instruction = encode(&instructions[i]);
		memory[WORD_LENGTH * i] = (int8_t)(MASK_BYTE_0 & instruction);
        memory[(WORD_LENGTH * i) + 1] = (int8_t)(MASK_BYTE_1 & instruction);
        memory[(WORD_LENGTH * i) + 2] = (int8_t)(MASK_BYTE_2 & instruction);
        memory[(WORD_LENGTH * i) + 3] = (int8_t)(MASK_BYTE_3 & instruction);
	}
}

void removeNewline(char *token) {
	token[strlen(token) - 1] = '\0';
}

int checkBrackets(char *token, char *temp) {
	if(token[0] == '[') {
		int i = 0;
		while(token[0] != ']') {
			temp[i] = token[0];
			token++;
			i++; 
		}
		temp[i] = token[0];
		token++;
		return 1;
	} 
	return 0;
}
