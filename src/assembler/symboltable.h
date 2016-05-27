#ifndef ARM11_19_SYMBOLTABLE_H
#define ARM11_19_SYMBOLTABLE_H

// Create new symbol table
struct SymbolTable *SymbolTable_new(void);

// Remove the symbol table from the heap (i.e. garbage collection)
void SymbolTable_delete(struct SymbolTable *symbolTable);

// Add matching label and value to symbol table
void SymbolTable_put(char *newLabel, void *newValue,
                     struct SymbolTable *symbolTable);

// Find value from given label
void *SymbolTable_get(char *key, struct SymbolTable symbolTable);

#endif //ARM11_19_SYMBOLTABLE_H
