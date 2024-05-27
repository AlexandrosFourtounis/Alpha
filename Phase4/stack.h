#define MAX_SIZE 10000

typedef struct {
    int arr[MAX_SIZE];
    int topp;
} Stack;

void initialize(Stack *stack);
int isEmpty(Stack *stack);
int isFull(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int topp(Stack *stack);
void print(Stack *stack);
