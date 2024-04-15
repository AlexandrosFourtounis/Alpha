#include "SymTable.h"

char *entry_types[] = {"GLOBAL", "LOCAL", "FORMAL", "USERFUNC", "LIBFUNC"};
char *libfuncs[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", "objectcopy", "totalarguments", "argument", "typeof", "strtonum", "sqrt", "cos", "sin"};

// Array of linked lists to store symbols for each scope
SymbolNode *scope_links[MAX_SCOPE + 1];

SymbolTableEntry *new_entry(const char *name, SymbolType type, unsigned int scope, unsigned int line){
    SymbolTableEntry *nentry = (SymbolTableEntry *)malloc(sizeof(SymbolTableEntry));
    assert(nentry);

    nentry -> isActive = 1;
    nentry -> type = type;

    switch(type){
        case USERFUNC:
        case LIBFUNC: {
            if(IS_FUNCTION(nentry)){
                nentry -> value.funcVal = malloc(sizeof(Function));
                assert(nentry -> value.funcVal);
                nentry -> value.funcVal ->name = strdup(name);
                nentry -> value.funcVal -> scope = scope;
                nentry -> value.funcVal -> line = line;
            }
            break;
        }
        default: {
            nentry -> value.varVal = malloc(sizeof(Variable));
            assert(nentry -> value.varVal);
            nentry -> value.varVal -> name = strdup(name);
            nentry -> value.varVal -> scope = scope;
            nentry -> value.varVal -> line = line;
            break;
        }
    }
    return nentry;
}

SymbolTableEntry *insert(const char *name, SymbolType type, unsigned int scope, unsigned int line){
    SymbolTableEntry *nentry = new_entry(name, type, scope, line);
    SymTable_put(symTable, name, nentry);
    insert_to_scope(nentry);
    return nentry;
}

SymbolTableEntry *lookup(const char *name, int scope) {
    assert(name);

    for (unsigned int curr_scope = 0; curr_scope <= 50; curr_scope++) {
        SymbolTableEntry *entry = lookup_in_scope(name, curr_scope);
        if (entry != NULL) {
            return entry;
        }
    }
    return NULL;
}
SymbolTableEntry *lookup_in_scope_hidden(const char *name, int scope)
{
    printf("scope inside lookup_in_scope_hidden: %d\n", scope);
    if (scope < 0)
        printf("negative scope error at SymbolTable.c line 60\n");
    SymbolNode *current = scope_links[scope];
    while (current != NULL)
    {
        if (!(current->entry->isActive))
        {
            const char *entryName;
            if (current->entry->type == GLOBAL || current->entry->type == LOCAL || current->entry->type == FORMAL)
            {
                entryName = current->entry->value.varVal->name;
            }
            else if (IS_FUNCTION(current->entry))
            {
                entryName = current->entry->value.funcVal->name;
            }
            if (strcmp(entryName, name) == 0)
            {
                return current->entry;
            }
        }
        current = current->next;
    }
    return NULL;
}

SymbolTableEntry *lookup_hidden(const char *name, int scope)
{
    assert(name);

    int curr_scope = scope;
    while (curr_scope >= 0){
        SymbolTableEntry *entry = lookup_in_scope_hidden(name, curr_scope);
        if (entry != NULL)
        {
            return entry;
        }
        curr_scope--;
    }
        

    return NULL;
}

SymbolTableEntry *lookup_in_scope(const char *name, int scope) {
    if(scope < 0 ) printf("negative scope error at SymbolTable.c line 60\n");
    SymbolNode *current = scope_links[scope];
    while (current != NULL) {
        if (current->entry->isActive) {
            const char *entryName;
            if (current->entry->type == GLOBAL || current->entry->type == LOCAL || current->entry->type == FORMAL) {
                entryName = current->entry->value.varVal->name;
            } else if (IS_FUNCTION(current->entry)) {
                entryName = current->entry->value.funcVal->name;
            }
            if (strcmp(entryName, name) == 0) {
                return current->entry;
            }
        }
        current = current->next;
    }
    return NULL;
}



SymbolTableEntry *lookup_without_active(const char *name, int scope) {
    assert(name);

    SymbolTableEntry *entry = (SymbolTableEntry *)SymTable_get(symTable, name);
    
    if (entry != NULL) {
        int entryScope;
        if (entry->type == GLOBAL || entry->type == LOCAL || entry->type == FORMAL) {
            entryScope = entry->value.varVal->scope;
        } else if (IS_FUNCTION(entry)) {
            entryScope = entry->value.funcVal->scope;
        }
        if (entryScope == scope) {
            return entry;
        }
    }

    return NULL;
}

void print_entry(void* entry)
{
    if (entry == NULL) {
        printf("NULL entry\n");
        return;
    }

    SymbolTableEntry* symtab = (SymbolTableEntry*) entry;
    int type = symtab->type;
    
    if(IS_FUNCTION(symtab)){
        printf("\"%s\" [%s] (line %u) (scope %u)\n", 
               symtab->value.funcVal->name, 
               entry_types[type], 
               symtab->value.funcVal->line, 
               symtab->value.funcVal->scope);
    }
    else{
        printf("\"%s\" [%s] (line %u) (scope %u)\n",
               symtab->value.varVal->name, 
               entry_types[type], 
               symtab->value.varVal->line, 
               symtab->value.varVal->scope);
    }
}

void free_entry(SymbolTableEntry *entry){
    if(entry == NULL){
        return;
    }
    if(IS_FUNCTION(entry)){
        free((char*)entry -> value.funcVal -> name);
        free(entry -> value.funcVal);
    }
    else{
        free((char*)entry -> value.varVal -> name);
        free(entry -> value.varVal);
    }
    free(entry);
}

void insert_libfuncs(){
    for(int i = 0; i < 12; i++){
        insert(libfuncs[i], LIBFUNC, 0, 0);
    }
}

void initialize_scope_links() {
    for (int i = 0; i <= MAX_SCOPE; i++) {
        scope_links[i] = NULL;
    }
}

void insert_to_scope(SymbolTableEntry *entry){
    assert(entry);
    int scope;
    if (entry->type == GLOBAL || entry->type == LOCAL || entry->type == FORMAL) {
        scope = entry->value.varVal->scope;
    } else if (IS_FUNCTION(entry)) {
        scope = entry->value.funcVal->scope;
    } 

    SymbolNode *node = (SymbolNode *)malloc(sizeof(SymbolNode));
    assert(node);
    node->entry = entry;
    node->next = scope_links[scope];
    scope_links[scope] = node;
}

void hide_scope(int scope) {
    SymbolNode *current = scope_links[scope];
    while (current != NULL) {
        current->entry->isActive = 0; 
        current = current->next;
    }
}

void unhide_scope(int scope) {
    SymbolNode *current = scope_links[scope];
    while (current != NULL) {
        current->entry->isActive = 1; 
        current = current->next;
    }
}

int is_hidden(SymbolTableEntry *entry) {
    return !entry->isActive;
}


void swap_nodes(SymbolNode *a, SymbolNode *b) {
    SymbolTableEntry *temp = a->entry;
    a->entry = b->entry;
    b->entry = temp;
}

void sort_entries_by_line(SymbolNode *head) {
    int swapped;
    SymbolNode *ptr1;
    SymbolNode *lptr = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->entry->value.varVal->line > ptr1->next->entry->value.varVal->line) {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_scope_links() {
    for (int i = 0; i <= MAX_SCOPE; i++) {
        if (scope_links[i] != NULL) {
            printf("- - - - - - - - - -  Scope #%d  - - - - - - - - - -\n", i);
            // Sort entries by line number before printing
            sort_entries_by_line(scope_links[i]);
            SymbolNode *current = scope_links[i];
            while (current != NULL) {
                print_entry(current->entry);
                current = current->next;
            }
            printf("\n");
        }
    }
}

void free_scope_links(){
    for (int i = 0; i <= MAX_SCOPE; i++) {
        SymbolNode *current = scope_links[i];
        while (current != NULL) {
            SymbolNode *next = current->next;
            free_entry(current->entry);
            free(current);
            current = next;
        }
    }
}
