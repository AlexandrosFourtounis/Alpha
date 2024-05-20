#include "funcstack.h"
#include <stdio.h>

void initialize_funcstack(funcstack *funcstack)
{
    funcstack->top = -1;
}

int isEmpty_funcstack(funcstack *funcstack)
{
    return (funcstack->top == -1);
}

int isFull_funcstack(funcstack *funcstack)
{
    return (funcstack->top == MAX_SIZE - 1);
}

void push_funcstack(funcstack *funcstack, int value)
{
    if (isFull_funcstack(funcstack))
    {
        printf("Error: funcstack overflow\n");
        return;
    }
    funcstack->arr[++funcstack->top] = value;
}

int pop_funcstack(funcstack *funcstack)
{
    if (isEmpty_funcstack(funcstack))
    {
        printf("Error: funcstack underflow\n");
        return -1;
    }
    return funcstack->arr[funcstack->top--];
}

int top_funcstack(funcstack *funcstack)
{
    if (isEmpty(funcstack))
    {
        printf("Error: funcstack is empty\n");
        return -1;
    }
    return funcstack->arr[funcstack->top];
}

void print_funcstack(funcstack *funcstack)
{
    if (isEmpty_funcstack(funcstack))
    {
        printf("funcstack is empty\n");
        return;
    }
    printf("funcstack elements: ");
    for (int i = funcstack->top; i >= 0; i--)
    {
        printf("%d ", funcstack->arr[i]);
    }
    printf("\n");
}