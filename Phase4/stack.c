#include "stack.h"
#include <stdio.h>

void initialize(Stack *stack) {
    stack->topp = -1;
}

int isEmpty(Stack *stack) {
    return (stack->topp == -1);
}

int isFull(Stack *stack) {
    return (stack->topp == MAX_SIZE - 1);
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Error: Stack overflow\n");
        return;
    }
    stack->arr[++stack->topp] = value;
}

int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack underflow\n");
        return -1;
    }
    return stack->arr[stack->topp--];
}

int topp(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        return -1;
    }
    return stack->arr[stack->topp];
}

void print(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = stack->topp; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}