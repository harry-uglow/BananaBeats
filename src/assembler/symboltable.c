/*
 * Implementation of a symbol table using a linked list of key-value pairs
 */

#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SymbolTableNode {
    char *label; // 'Key' of the symbol table, the label
    int address; // 'Value' of the symbol table, the memory address

    struct SymbolTableNode *pNextNode; // The next node (node linked to)
};

struct SymbolTable {
    struct SymbolTableNode *pFirstNode;
};

// Create new symbol table
struct SymbolTable *SymbolTable_new(void) {
    // Assign new symbol table to heap
    struct SymbolTable *newSymbolTable
            = malloc(sizeof(struct SymbolTable));

    // Exit the program if assigning to the heap has failed
    if (newSymbolTable == NULL) {
        printf("Error assigning new symbol table to the heap\n");
        exit(1);
    }

    // Make sure that the head node of the symbol table is null
    newSymbolTable->pFirstNode = NULL;

    return newSymbolTable;
}

// Remove the symbol table from the heap (i.e. garbage collection)
void SymbolTable_delete(struct SymbolTable *symbolTable) {
    // Check that the argument doesn't point to null
    if (symbolTable == NULL) {
        printf("The table doesn't exist");
        return;
    }

    // Remove all nodes
    struct SymbolTableNode *pCurrent = symbolTable->pFirstNode;
    struct SymbolTableNode *pNext;

    while (pCurrent != NULL) {
        pNext = pCurrent->pNextNode; // Update next node
        free(pCurrent); // Free the node itself
        pCurrent = pNext;
    }

    free(symbolTable); // Free the table
}

// Add matching label and address to symbol table
void SymbolTable_put(char *newLabel, int newAddress,
                     struct SymbolTable *symbolTable) {
    // Make sure no arguments are null
    if (newLabel == NULL || symbolTable == NULL) {
        printf("Error: null argument. Did not add entry to symbol table\n");
        return;
    }

    // Create new node and assign it to the heap
    struct SymbolTableNode *newNode = malloc(sizeof(struct SymbolTableNode));

    // Exit the program if assigning to the heap has failed
    if (newNode == NULL) {
        printf("Error assigning new node to the heap\n");
        exit(1);
    }

    // Assign the key and value of the new node
    newNode->label = newLabel;
    newNode->address = newAddress;

    // Node links to current head of symbol table
    newNode->pNextNode = symbolTable->pFirstNode;
    symbolTable->pFirstNode = newNode; // Make new node the head of the table
}

// Find address from given label
int SymbolTable_get(char *key, struct SymbolTable symbolTable) {
    struct SymbolTableNode *pCurrent = symbolTable.pFirstNode;

    // Loop to traverse through table until address value is found
    while (pCurrent != NULL) {
        if (!strcmp(pCurrent->label, key)) {
            return pCurrent->address;
        }
        pCurrent = pCurrent->pNextNode; // Update to next node
    }
    return 0; // Assuming the input is well-formed, code should not reach here
}

int main() {
    printf("test\n");
    // TODO: Test this
    return EXIT_SUCCESS;
}
