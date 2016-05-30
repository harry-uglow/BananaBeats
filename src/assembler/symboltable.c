/*
 * Implementation of a symbol table using a linked list of key-value pairs,
 * where the key is a string
 */

#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SymbolTableNode {
    char *label; // 'Key' of the symbol table, the label
    void *value; // 'Value' of the symbol table. Pointer to a value

    struct SymbolTableNode *pNextNode; // The next node (node linked to)
};

typedef struct SymbolTable {
    struct SymbolTableNode *pFirstNode;
} symbolTable_t;

// Create new symbol table
symbolTable_t*SymbolTable_new(void) {
    // Assign new symbol table to heap
    symbolTable_t*newSymbolTable
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
void SymbolTable_delete(symbolTable_t*symbolTable) {
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
        free(pCurrent->value);
        free(pCurrent->label);
        free(pCurrent); // Free the node itself
        pCurrent = pNext;
    }

    free(symbolTable); // Free the table
}

// Add matching label and value to symbol table
void SymbolTable_put(char *newLabel, void *newValue,
                     symbolTable_t*symbolTable) {
    // Make sure no arguments are null
    if (newLabel == NULL || newValue == NULL || symbolTable == NULL) {
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
    newNode->value = newValue;

    // Node links to current head of symbol table
    newNode->pNextNode = symbolTable->pFirstNode;
    symbolTable->pFirstNode = newNode; // Make new node the head of the table
}

// Find value from given label
void *SymbolTable_get(char *key, symbolTable_tsymbolTable) {
    struct SymbolTableNode *pCurrent = symbolTable.pFirstNode;

    // Loop to traverse through table until value value is found
    while (pCurrent != NULL) {
        if (!strcmp(pCurrent->label, key)) {
            return pCurrent->value;
        }
        pCurrent = pCurrent->pNextNode; // Update to next node
    }
    return 0; // Assuming the input is well-formed, code should not reach here
}
