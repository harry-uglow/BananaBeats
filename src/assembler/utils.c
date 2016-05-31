#include "utils.h"
#include <stdio.h>
#include <memory.h>


int firstPass(char **argv) {
	// Open file to read from
	FILE *finput = fopen(argv[1],"r");
	
	// Check if assembly file cannot be opened
	if (finput == NULL) {
		printf("Could not open file %s\n", argv[1]);
		return 0;
	}

	char *buffer = calloc(MAX_LINE_LENGTH, sizeof(char));
	char *token;
	char *ops = calloc(MAX_OPERAND_LENGTH, sizeof(char));
	char *rest;
	char *temp = calloc(MAX_OPERAND_LENGTH, sizeof(char));

	while(fgets(buffer, MAX_LINE_LENGTH, finput) != NULL) {		
		// Remove '\n' character at the end of the string
		removeNewline(buffer);
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
		for(int i = 1; i <= 4; i++) {
            if(!rest) {
                break;
            }
			if(rest[0] == '[') {
                int j = 0;
                while(rest[0] != ']') {
                    temp[j] = rest[0];
                    rest++;
                    j++;
                }
                temp[j] = rest[0];
                temp[j + 1] = '\0';
                strcpy(ops, temp);
                rest++;
            } else {
				strcpy(ops, strtok(rest, TOK_DELIM));
                rest = strtok(NULL, "");
			}
            if(ops != NULL) {
                switch (i) {
                    case 1 :
                        strcpy(instruction[address].op1, ops);
                        break;
                    case 2 :
                        strcpy(instruction[address].op2, ops);
                        break;
                    case 3 :
                        strcpy(instruction[address].op3, ops);
                        break;
                    case 4 :
                        strcpy(instruction[address].op4, ops);
                        break;
                    default:
                        break;
                }
            }
		}
	
		/*// Set all non-null operands to components of assembly instructions
		if(ops[0] != NULL) {
            strcpy(instruction[address].op1, ops[0]);
		}

        if(ops[1] != NULL) {
            strcpy(instruction[address].op1, ops[1]);
        }

        if(ops[2] != NULL) {
            strcpy(instruction[address].op1, ops[2]);
        }

        if(ops[3] != NULL) {
            strcpy(instruction[address].op1, ops[3]);
        }*/
		
		// Increment address
		address++;
	}
		
	// Finished reading input of assembly file
	fclose(finput);
	return 1;
}

int initialiseAssembler() {
	// Allocate memory onto the heap for an array of instructions
	instruction = calloc(MEM_SIZE, sizeof(assIns_t));

    // Check if memory allocation failed
    if(instruction == NULL) {
        printf("Memory could not be allocated onto the heap.\n");
        return 0;
    }

    for(int i = 0; i < MEM_SIZE; i++) {
        instruction[i].mnemonic = calloc(MAX_MNEMONIC_LENGTH, sizeof(char));
        instruction[i].op1 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op2 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op3 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op4 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
    }

    memory = calloc(MEM_SIZE, sizeof(int8_t));

    // Create new symbol table
	table = *SymbolTable_new();

	// Initialise address counter
	address = 0;
	return 1;
}

int writeToBinaryFile(char **argv) {
	// Open file to write to
	FILE *foutput = fopen(argv[2], "wb");

	// Check if file cannot be opened
	if(foutput == NULL) {
		printf("Could not open file %s\n", argv[2]);
		return 0;
	}
	
	// Write all of the binary instructions encoded into the output file
	for(int i = 0; i < address * 4; i++) {
		fwrite(&memory[i], sizeof(int8_t), 1, foutput);
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

void secondPass() {
	for(int i = 0; i < (sizeof(*instruction) / sizeof(instruction[0])); i++) {
        assIns_t assIns = instruction[i];
		int32_t ins = encode(&assIns);
		memory[WORD_LENGTH * i] = (int8_t)(MASK_BYTE_0 & ins);
        memory[(WORD_LENGTH * i) + 1] = (int8_t)(MASK_BYTE_1 & ins);
        memory[(WORD_LENGTH * i) + 2] = (int8_t)(MASK_BYTE_2 & ins);
        memory[(WORD_LENGTH * i) + 3] = (int8_t)(MASK_BYTE_3 & ins);
	}
}

void removeNewline(char *token) {
	token[strlen(token) - 1] = '\0';
}

