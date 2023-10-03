#ifndef STACK_H
#define STACK_H

struct StackNode {
    char data;
    struct StackNode *next;
};

struct Stack {
    struct StackNode *top;
};

struct Stack *init();
void push(struct Stack *stack, char data);
char pop(struct Stack *stack);
void destroy(struct Stack *stack);

#endif