#include "symtablehash.h"

#define HASH_MULTIPLIER 65599
#define BUCKETS 509


struct Binding {
    char* key;
    void* value;
    struct Binding *next;
};
	
/* Return a hash code for pcKey. */
static unsigned int SymTable_hash(const char *pcKey)
{
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash;
}

SymTable_T SymTable_new(void)
{
    int i;
    SymTable_T newsym = malloc(sizeof(struct SymTable)); 
    newsym -> table = malloc(BUCKETS*sizeof(struct Binding*));
    newsym -> length = 0;
    newsym -> buckets = BUCKETS;

    for (i = 0; i < BUCKETS; i++) 
    {
        newsym -> table[i] = NULL;
    }
    return newsym;
}

void SymTable_free(SymTable_T oSymTable) 
{
    struct Binding *tmp;
    struct Binding *next;
    size_t i;

    if (!oSymTable) {
        return;
    }

    for (i = 0; i < oSymTable->buckets; i++) {
        tmp = oSymTable->table[i];
        while (tmp) {
            next = tmp->next;
            if (tmp->key) {
                free(tmp->key);
            }
            free(tmp);
            tmp = next;
        }
    }
    free(oSymTable->table);
    free(oSymTable);
}

unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable);
    return oSymTable -> length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) 
{
    struct Binding *tmp;
    struct Binding *newbind;
    unsigned int hash;
    int index;
    assert(oSymTable);
    assert(pcKey);

    /* Compute the hash value for the key */
    hash = SymTable_hash(pcKey);
    index = hash % oSymTable->buckets;

    /* Check if the key already exists in the table */
    for (tmp = oSymTable->table[index]; tmp != NULL; tmp = tmp->next) {
        if (strcmp(pcKey, tmp->key) == 0) {
            return 0;
        }
    }
    /* Create a new binding for the key and value */
    newbind = (struct Binding*)malloc(sizeof(struct Binding));
    if (newbind == NULL) {
        return 0;
    }
    newbind->value = (void*)pvValue;
    newbind->next = oSymTable->table[index];
    oSymTable->table[index] = newbind;
    newbind->key = (char*)malloc((strlen(pcKey) + 1) * sizeof(char));
    if (newbind->key == NULL) {
        free(newbind);
        return 0;
    }
    newbind->key = strcpy(newbind->key, pcKey);
    (oSymTable->length)++;
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    unsigned int uiBucket;
    struct Binding *tmp;
    struct Binding *previous;

    assert(oSymTable);
    assert(pcKey);

    uiBucket = SymTable_hash(pcKey) % oSymTable->buckets;
    tmp = oSymTable->table[uiBucket];
    previous = NULL;

    while (tmp != NULL) {
        if (strcmp(tmp->key, pcKey) == 0) {
            if (previous == NULL) {
                oSymTable->table[uiBucket] = tmp->next;
            } else {
                previous->next = tmp->next;
            }
            free(tmp->key);
            free(tmp);
            oSymTable->length--;
            return 1;
        }
        previous = tmp;
        tmp = tmp->next;
    }

    return 0;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) 
{
    unsigned int uiBucket;
    struct Binding *tmp;
    assert(oSymTable);
    assert(pcKey);

    uiBucket = SymTable_hash(pcKey) % oSymTable->buckets;

    tmp = oSymTable->table[uiBucket];
    while (tmp) 
    {
        if (strcmp(tmp->key, pcKey) == 0) {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
    unsigned int index;
    struct Binding *tmp;
    assert(oSymTable);
    assert(pcKey);

    index = SymTable_hash(pcKey) % oSymTable->buckets;
    tmp = oSymTable->table[index];

    while (tmp != NULL)
    {
        if (strcmp(tmp->key, pcKey) == 0)
        {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue,void *pvExtra),const void *pvExtra)
{
    struct Binding *tmp;
    unsigned int i;

    assert(oSymTable);
    assert(pfApply);

    for (i = 0; i < oSymTable->buckets; i++)
    {
        tmp = oSymTable->table[i];
        while (tmp != NULL)
        {
            (*pfApply)(tmp->key, tmp->value, (void*)pvExtra);
            tmp = tmp->next;
        }
    }
}