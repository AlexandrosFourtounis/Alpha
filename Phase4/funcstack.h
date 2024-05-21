#define MAX_SIZE 10000

typedef struct
{
    int arr[MAX_SIZE];
    SymbolTableEntry *top;
} funcstack;


void initialize_funcstack(funcstack *funcstack);
int isEmpty_funcstack(funcstack *funcstack);
int isFull_funcstack(funcstack *funcstack);
void push_funcstack(funcstack *funcstack, int value);
int pop_funcstack(funcstack *funcstack);
int top_funcstack(funcstack *funcstack);
void print_funcstack(funcstack *funcstack);
