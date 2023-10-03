#include <stdlib.h>

struct StackNode {
    char data;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
};

struct Stack *init() {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    if (!stack) {
        return NULL;
    }
    stack->top = NULL;
    return stack;
}

void push(struct Stack *stack, char data) {
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (!newNode) {
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

char pop(struct Stack *stack) {
    if (stack->top == NULL) {
        return -1;
    }
    struct StackNode *temp = stack->top;
    char data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

void destroy(struct Stack *stack) {
    while (stack->top != NULL) {
        struct StackNode *temp = stack->top;
        stack->top = temp->next;
        free(temp);
    }
    free(stack);
}