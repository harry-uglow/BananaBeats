#ifndef ARM11_19_SYMBOLTABLE_H
#define ARM11_19_SYMBOLTABLE_H

typedef struct SymbolTableNode {
    char *label; // 'Key' of the symbol table, the label
    void *value; // 'Value' of the symbol table. Pointer to a value

    struct SymbolTableNode *pNextNode; // The next node (node linked to)
} symbolTableNode_t;

typedef struct SymbolTable {
    symbolTableNode_t *pFirstNode;
} symbolTable_t;

// Create new symbol table
symbolTable_t *SymbolTable_new(void);

// Remove the symbol table from the heap (i.e. garbage collection)
void SymbolTable_delete(struct SymbolTable *symbolTable);

// Add matching label and value to symbol table
void SymbolTable_put(char *newLabel, void *newValue,
                     struct SymbolTable *symbolTable);

// Find value from given label
void *SymbolTable_get(char *key, struct SymbolTable symbolTable);

#endif //ARM11_19_SYMBOLTABLE_H
