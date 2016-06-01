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
	
	// Declare buffer string to hold each line in assembly file
	char *buffer = calloc(MAX_LINE_LENGTH, sizeof(char));
	// Declare token string to hold mnemonic part of assembly instruction
	char *token;
	// Declare rest string to hold the rest of the assembly instruction 	
	char *rest;
	// Declare ops string to hold operands of each instruction
	char *ops = calloc(MAX_OPERAND_LENGTH, sizeof(char));
	// Declare temp string to hold bracketed operands of assembly instruction
	char *temp = calloc(MAX_OPERAND_LENGTH, sizeof(char));
	// Declare 16 bit integer to hold value of the current address
	int16_t *currAddress = malloc(sizeof(int16_t));
	
	while(fgets(buffer, MAX_LINE_LENGTH, finput) != NULL) {
        // Skip spaces at the beginning of a line
        while(buffer[0] == ' ') {
            buffer++;
        }
        // Skip blank lines
        if(buffer[0] == '\n') {
            continue;
        }
		// Remove '\n' character at the end of the string
		removeNewline(buffer);
		// Extract first token in string (the mnemonic) 
		token = strtok(buffer, TOK_DELIM);
        // Rest will hold the rest of the string (the operands)
		rest = strtok(NULL, "");

        
		// Check if first token is label or mnemonic
        if(isLabel(token)) {
            // Declare label string to hold label and act as buffer for token
            char *label = calloc(MAX_OPERAND_LENGTH, sizeof(char));
           	// Copy token to label buffer
			strcpy(label, token);
			// Assign current address to currAdress
            *currAddress = (int16_t) address;
			// Insert the label with the corresponding current address into symbol table
            SymbolTable_put(label, currAddress, &table);
			// Continue to next instruction by skipping current iteration of while loop
            continue;
        } else {
			// Assign token as value of mnemonic in the instruction at 'address'
            strcpy(instruction[address].mnemonic, token);
		}
	
		// Loop for up to 4 operands and assign operands to instruction at 'address'
		for(int i = 1; i <= 4; i++) {
			// If there are no more operands left then break from the loop
            if(!rest || rest[0] == '\0') {
                break;
            }

            // Skip through spaces at the beginning of operands
            while(rest[0] == ' ') {
                rest++;
            }
		
			// Check if current expression is a bracketed expression
			// and if it is then iterate through the characters and 
			// copy them to the temp string until the you encounter 
			// a ']' character. Once the end bracket is reached then 
			// copy it to the end of temp, add a null terminater for 
			// temp string and increment the rest pointer to point to 
			// the next character after ']'
			if(rest[0] == '[') {
                int j = 0;
                while(rest[0] != ']') {
                    temp[j] = rest[0];
                    rest++;
                    j++;
                }
                temp[j] = rest[0];
                temp[j + 1] = '\0';

				// Copy the temp operand into the ops string
                strcpy(ops, temp);
				// Increment rest pointer to point to next character
                rest++;
            } else {
				// Copy next tokenised operand into ops string
				strcpy(ops, strtok(rest, TOK_DELIM));
				// Reassing the rest of the assembly instruction to rest
                rest = strtok(NULL, "");
			}
			// If ops string is not null & contains an operand then 
			// copy it to the correct component of the assembly instruction
			// at 'address'. Otherwise do nothing since there is no operand
			// to add to the assembly instruction.
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
		// Increment the address counter to hold the next assembly instruction to be tokenised
		address++;
	}
	// Free memory allocated onto the heap for local variables
	if(buffer != NULL) {
		free(buffer);
	}
	
	if(ops != NULL) {
		free(ops);
	}
	
	if(temp != NULL) {
		free(temp);
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
	
	// Allocate memory for every component of each assIns_t in instruction
	// and initialise them with calloc
    for(int i = 0; i < MEM_SIZE; i++) {
        instruction[i].mnemonic = calloc(MAX_MNEMONIC_LENGTH, sizeof(char));
        instruction[i].op1 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op2 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op3 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
        instruction[i].op4 = calloc(MAX_OPERAND_LENGTH, sizeof(char));
    }
	
	// Allcoate memory on the heap for 'memory' array & initialise
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
	
	// Write all of the encoded binary instructions into the output file
	for(int i = 0; i < address * WORD_LENGTH; i++) {
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
    numStoredConstants = 0;
	for(int i = 0; i < address - numStoredConstants; i++) {
        assIns_t assIns = instruction[i];
		int32_t ins = encode(&assIns);
		memory[WORD_LENGTH * i] = (int8_t)(MASK_BYTE_0 & ins);
        memory[(WORD_LENGTH * i) + 1] = (int8_t)((MASK_BYTE_1 & ins) >> 8);
        memory[(WORD_LENGTH * i) + 2] = (int8_t)((MASK_BYTE_2 & ins) >> 16);
        memory[(WORD_LENGTH * i) + 3] = (int8_t)((MASK_BYTE_3 & ins) >> 24);
	}
}

void removeNewline(char *token) {
	token[strlen(token) - 1] = '\0';
}

void freeInstructions(void) {
	for(int i = 0; i < MEM_SIZE; i++) {
		if(instruction[i].mnemonic != NULL) {
			free(instruction[i].mnemonic);
		}
		
		if(instruction[i].op1 != NULL) {
			free(instruction[i].op1);
		}	
		
		if(instruction[i].op2 != NULL) {
			free(instruction[i].op2);
		}	
		
		if(instruction[i].op3 != NULL) {
			free(instruction[i].op3);
		}			
		
		if(instruction[i].op4 != NULL) {
			free(instruction[i].op4);
		}
	}
}
