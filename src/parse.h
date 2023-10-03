#ifndef PARSE_H
#define PARSE_H

#define NUMBER 0
#define OPERATOR 1
#define OPEN_PAREN 2
#define CLOSE_PAREN 3
#define FUNCTION 4


struct Token {
    int type;
    char value[32];
};

int isAlphabetic(char c);
int isDigit(char c);
int parse_input(char* ptr, struct Token (*tokens)[100], int* tokenCount);

#endif