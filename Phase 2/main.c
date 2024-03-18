#include <stdio.h>
#include "SymTable.h"

SymTable_T symTable = NULL;

int main() {

    symTable = SymTable_new();
    initialize_scope_links();
    insert_libfuncs();
    
    SymbolTableEntry *entry1 = insert("var1", GLOBAL, 0, 10);
    SymbolTableEntry *entry2 = insert("func1", USERFUNC, 0, 20);
    SymbolTableEntry *entry3 = insert("func2", LIBFUNC, 1, 30);

    printf("Symbol Table Entries:\n");
    printf("=====================\n");
    SymbolTableEntry* entries[] = {entry1, entry2, entry3};
    int num_entries = sizeof(entries) / sizeof(entries[0]);

    for (int i = 0; i < num_entries; i++) {
        printf("Entry %d:\n", i + 1);
        print_entry(entries[i]);
    }

    printf("\nScope Links:\n");
    print_scope_links();
    printf("\nHiding scope 0:\n");
    printf("=====================\n");
    hide_scope(0);
    is_hidden(entry1) ? printf("Entry 1 is hidden.\n") : printf("Entry 1 is not hidden.\n");

    printf("\nTesting Lookup Function:\n");
    printf("========================\n");
    const char *name_to_lookup = "var1";
    SymbolTableEntry *lookup_result = lookup_in_scope(name_to_lookup, 0);
    if (lookup_result != NULL) {
        printf("Lookup Result for \"%s\":\n", name_to_lookup);
        print_entry(lookup_result);
    } else {
        printf("Symbol \"%s\" not found in the symbol table.\n", name_to_lookup);
    }

    printf("\nTesting Lookup Function without Active Scope 0:\n");
    printf("=================================================\n");
    lookup_result = lookup_without_active(name_to_lookup, 0);
    if (lookup_result != NULL) {
        printf("Lookup Result for \"%s\":\n", name_to_lookup);
        print_entry(lookup_result);
    } else {
        printf("Symbol \"%s\" not found in the symbol table.\n", name_to_lookup);
    }


    printf("\nUnhiding scope 0:\n");
    printf("=====================\n");
    unhide_scope(0);

    printf("\nTesting Lookup Function After Unhiding Scope 0:\n");
    printf("=================================================\n");
    lookup_result = lookup_in_scope(name_to_lookup, 0);
    if (lookup_result != NULL) {
        printf("Lookup Result for \"%s\":\n", name_to_lookup);
        print_entry(lookup_result);
    } else {
        printf("Symbol \"%s\" not found in the symbol table.\n", name_to_lookup);
    } 

    SymTable_free(symTable);
    free_scope_links();

    return 0;
}

