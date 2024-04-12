#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "symtablehash.h"

#define IS_FUNCTION(entry) (entry->type == USERFUNC || entry->type == LIBFUNC)
#define MAX_SCOPE 5

extern char *entry_types[];
extern char *libfuncs[12];
extern SymTable_T symTable;

typedef struct Variable {
    const char *name;
    unsigned int scope;
    unsigned int line;
} Variable;

typedef struct Function {
    const char *name;
    unsigned int scope;
    unsigned int line;
} Function;

typedef enum SymbolType{
    GLOBAL, LOCAL, FORMAL, USERFUNC, LIBFUNC
}SymbolType;

typedef struct SymbolTableEntry{
    int isActive;
    union{
        Variable *varVal;
        Function *funcVal;
    }value;
    enum SymbolType type;
    
}SymbolTableEntry;

// Structure to represent a symbol node in the scope link
typedef struct SymbolNode {
    SymbolTableEntry *entry;
    struct SymbolNode *next;
} SymbolNode;

SymbolTableEntry *new_entry(const char *name, SymbolType type, unsigned int scope, unsigned int line);
SymbolTableEntry *insert(const char *name, SymbolType type, unsigned int scope, unsigned int line);
SymbolTableEntry *lookup(const char *name, int scope);
SymbolTableEntry *lookup_in_scope(const char *name, int scope);
SymbolTableEntry *lookup_without_active(const char *name, int scope);
void print_entry(void*);
void free_entry(SymbolTableEntry *entry);
void insert_libfuncs();

// Function to initialize the scope links
void initialize_scope_links();
void insert_to_scope(SymbolTableEntry *entry);
void hide_scope(int scope);
void unhide_scope(int scope);
int is_hidden(SymbolTableEntry *entry);
void sort_entries_by_line(SymbolNode *head);
//helper function to swap two nodes for sorting in the scope link
void swap_nodes(SymbolNode *a, SymbolNode *b);
void print_scope_links();
void free_scope_links();