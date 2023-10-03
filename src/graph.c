#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "stack.h"
#include <math.h>


#define NUMBER 0
#define OPERATOR 1
#define OPEN_PAREN 2
#define CLOSE_PAREN 3
#define FUNCTION 4

#define Y 25
#define X 80
#define XSTEP (M_PI / 20)


int get_input(char** ptr);
int infixToPostfix(struct Token *infixTokens, int tokenCount, struct Token *postfixTokens, int postfixIndex);
int priority(char op1, char op2);
int getPriority(char operator);
double pol_math(struct Token a[100], int count, double x);
void res_func(struct Token a[100], int postfixIndex, double *res);
void initgrid(int grid[Y][X]);
void printscreen(int grid[Y][X]);
void graph(double *res, int grid[Y][X]);



int main(void) {
    char* ptr = NULL;
    get_input(&ptr);
    int tokenCount = 0;
    struct Token tokens[100]; 
    parse_input(ptr, &tokens, &tokenCount);

    struct Token polish[100];
    int postfixIndex = 0;
    postfixIndex = infixToPostfix(tokens, tokenCount, polish, postfixIndex);
 
    

    double res[80] = {0};
    int grid[Y][X];
    initgrid(grid); 
    res_func(polish, postfixIndex, res);
    graph(res, grid); 
    printscreen(grid); 

    return 0;
}




int get_input(char** ptr) {
    int n = 1;
    int index = 0;
    int flag = 0;
    *ptr = (char*)malloc(n * sizeof(char));
    while(1) {
        int res = scanf("%c", &(*ptr)[index]);
        if (res == 1) {
            if ((*ptr)[index] != '\n'){
                n++;
                index++;
                *ptr = (char*)realloc(*ptr, n * sizeof(char));
            } else {
                break;
            }
        } else {
            flag = 1;
            break;
        }
    }
    if (flag != 0) {
        printf("n/a");
    }
    return n;
}


int infixToPostfix(struct Token *infixTokens, int tokenCount, struct Token *postfixTokens, int postfixIndex) {
    struct Stack *stack = init();
    

    for (int i = 0; i < tokenCount; i++) {
        if (infixTokens[i].type == OPERATOR) {
            while (stack->top != NULL && priority(stack->top->data, infixTokens[i].value[0])) {
                postfixTokens[postfixIndex].type = OPERATOR;
                postfixTokens[postfixIndex++].value[0] = pop(stack);
            }
            push(stack, infixTokens[i].value[0]);
        } else if (infixTokens[i].type == OPEN_PAREN) {
            push(stack, '(');
        } else if (infixTokens[i].type == CLOSE_PAREN) {
            while (stack->top != NULL && stack->top->data != '(' && priority(stack->top->data, infixTokens[i].value[0])) {
                postfixTokens[postfixIndex].type = OPERATOR;
                postfixTokens[postfixIndex++].value[0] = pop(stack);
            }
            if (stack->top != NULL && stack->top->data == '(') {
                pop(stack); 
            }
        } else if (infixTokens[i].type == FUNCTION) {
            push(stack, infixTokens[i].value[0]);
        } else {
            postfixTokens[postfixIndex++] = infixTokens[i];
        }
    }

    while (stack->top != NULL) {
        postfixTokens[postfixIndex].type = OPERATOR;
        postfixTokens[postfixIndex++].value[0] = pop(stack);
    }

    destroy(stack);

    return postfixIndex;
}

int priority(char op1, char op2) {
    int priority1 = getPriority(op1);
    int priority2 = getPriority(op2);

    return priority1 < priority2;
}

int getPriority(char operator) {
    switch (operator) {
        case '(':
        case ')':
            return 5;
        case '^':
            return 4;
        case 's':
        case 'c':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

double pol_math(struct Token a[100], int count, double x) {
    double line[300] = {0.0};
    int sp = 0;
    int id = 0;

    if (a[id].value[0] == '\0') {
        return 0.0;
    }

    while (a[id].value[0] == '\0'){
        
    }
    while (id < count) {
        switch (a[id].value[0]) {
            case '+':
                line[sp - 2] += line[sp - 1];
                sp--;
                break;
            case '-':
                line[sp - 2] -= line[sp - 1];
                sp--;
                break;
            case '*':
                line[sp - 2] *= line[sp - 1];
                sp--;
                break;
            case '/':
                line[sp - 2] /= line[sp - 1];
                sp--;
                break;
            case 's':
                line[sp - 1] = sin(line[sp - 1]);
                break;
            case 'c':
                line[sp - 1] = cos(line[sp - 1]);
                break;
            case 't':
                line[sp - 1] = tan(line[sp - 1]);
                break;
            case 'g':
                line[sp - 1] = 1.0 / tan(line[sp - 1]);
                break;
            case 'q':
                line[sp - 1] = sqrt(line[sp - 1]);
                break;
            case 'l':
                line[sp - 1] = log(line[sp - 1]);
                break;
            case 'x':
                line[sp] = x;
                sp++;
                break;
            default:
                line[sp] = atof(a[id].value);
                sp++;
        }
        id++;
    }

    return line[sp - 1];
}

void graph(double *res, int grid[Y][X]) {
    for (int j = 0; j < X; j++) {
        for (int i = 0; i < Y; i++) {
            if ((round(res[j] * 24 / 2)) + 12 == i) {
                grid[i][j] = 1;
            }
        }
    }
}

void initgrid(int grid[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            grid[i][j] = 0;
        }
    }
}

void printscreen(int grid[Y][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (grid[i][j] == 0) {
                printf(".");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

void res_func(struct Token a[100], int postfixIndex, double *res) {
    for (int i = 0; i < X; i++) {
        res[i] = pol_math(a, postfixIndex, XSTEP * i);
    }
}