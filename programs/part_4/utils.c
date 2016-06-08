/*
 * Implementation of a symbol table using a linked list of key-value pairs,
 * where the key is a string
 */

#include "symbolTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create new symbol table
symbolTable_t *SymbolTable_new(void) {
    // Assign new symbol table to heap
    symbolTable_t *newSymbolTable
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
void SymbolTable_delete(symbolTable_t *symbolTable) {
    // Check that the argument doesn't point to null
    if (symbolTable == NULL) {
        printf("The table doesn't exist");
        return;
    }

    // Remove all nodes
    symbolTableNode_t *pCurrent = symbolTable->pFirstNode;
    symbolTableNode_t *pNext;

    while (pCurrent) {
        pNext = pCurrent->pNextNode; // Update next node
        pCurrent = pNext;
    }

    // TODO: uncomment this when bug is fixed
    // free(symbolTable); // Free the table
}

// Add matching pin and sound to symbol table
void SymbolTable_put(int *newPin, char *newSound,
                     symbolTable_t *symbolTable) {
    // Make sure no arguments are null
    if (newPin == NULL || newSound == NULL || symbolTable == NULL) {
        printf("Error: null argument. Did not add entry to symbol table\n");
        return;
    }

    // Create new node and assign it to the heap
    symbolTableNode_t *newNode = malloc(sizeof(struct SymbolTableNode));

    // Exit the program if assigning to the heap has failed
    if (newNode == NULL) {
        printf("Error assigning new node to the heap\n");
        exit(1);
    }

    // Assign the key and value of the new node
    newNode->pin = newPin;
    newNode->sound = newSound;

    // Node links to current head of symbol table
    newNode->pNextNode = symbolTable->pFirstNode;
    symbolTable->pFirstNode = newNode; // Make new node the head of the table
}

// Find sound file from given pin
void *SymbolTable_get(int pin, symbolTable_t *symbolTable) {
    symbolTableNode_t *pCurrent = (*symbolTable).pFirstNode;

    // Loop to traverse through table until sound file is found
    while (pCurrent != NULL) {
        if (pCurrent->pin == pin) {
            return pCurrent->sound;
        }
        pCurrent = pCurrent->pNextNode; // Update to next node
    }
    return 0; // Assuming the input is well-formed, code should not reach here
}
