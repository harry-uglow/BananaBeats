#ifndef ARM11_19_SYMBOLTABLE_H
#define ARM11_19_SYMBOLTABLE_H

typedef struct SymbolTableNode {
    int pin; // 'Key' of the symbol table, the pin number
    char *sound // 'Value' of the symbol table (sound file)
    struct SymbolTableNode *pNextNode; // The next node (node linked to)
} symbolTableNode_t;

typedef struct SymbolTable {
    symbolTableNode_t *pFirstNode;
} symbolTable_t;

// Create new symbol table
symbolTable_t *SymbolTable_new(void);

// Remove the symbol table from the heap (i.e. garbage collection)
void SymbolTable_delete(symbolTable_t *symbolTable);

// Add matching label and value to symbol table
void SymbolTable_put(int *newPin, char *newSound,
                     symbolTable_t *symbolTable);

// Find value from given label
void *SymbolTable_get(int pin, symbolTable_t *symbolTable);

#endif //ARM11_19_SYMBOLTABLE_H
