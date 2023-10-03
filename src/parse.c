#include "parse.h"

#include <stdio.h>
#include <string.h>

int isAlphabetic(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }

int isDigit(char c) { return (c >= '0' && c <= '9'); }

int parse_input(char* ptr, struct Token (*tokens)[100], int* tokenCount) {
    while (*ptr) {
        if (isDigit(*ptr) || (*ptr == '.')) {
            int numLength = 0;
            while (isDigit(*ptr) || (*ptr == '.')) {
                (*tokens)[*tokenCount].value[numLength] = *ptr;
                numLength++;
                ptr++;
            }
            (*tokens)[*tokenCount].value[numLength] = '\0';
            (*tokens)[*tokenCount].type = NUMBER;
            (*tokenCount)++;
            continue;
        }
        if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/') {
            (*tokens)[*tokenCount].type = OPERATOR;
            (*tokens)[*tokenCount].value[0] = *ptr;
            (*tokens)[*tokenCount].value[1] = '\0';
            (*tokenCount)++;
        }
        if (*ptr == '(') {
            (*tokens)[*tokenCount].type = OPEN_PAREN;
            (*tokens)[*tokenCount].value[0] = *ptr;
            (*tokens)[*tokenCount].value[1] = '\0';
            (*tokenCount)++;
        }
        if (*ptr == ')') {
            (*tokens)[*tokenCount].type = CLOSE_PAREN;
            (*tokens)[*tokenCount].value[0] = *ptr;
            (*tokens)[*tokenCount].value[1] = '\0';
            (*tokenCount)++;
        }
        if (isAlphabetic(*ptr)) {
            int funcLength = 0;
            char funcValue;
            if (strncmp(ptr, "sin", 3) == 0) {
                funcValue = 's';
                funcLength = 3;
            } else if (strncmp(ptr, "cos", 3) == 0) {
                funcValue = 'c';
                funcLength = 3;
            } else if (strncmp(ptr, "tg", 2) == 0) {
                funcValue = 't';
                funcLength = 2;
            } else if (strncmp(ptr, "ctg", 3) == 0) {
                funcValue = 'g';  
                funcLength = 3;
            } else if (strncmp(ptr, "sqrt", 4) == 0) {
                funcValue = 'q';  
                funcLength = 4;
            } else if (strncmp(ptr, "ln", 2) == 0) {
                funcValue = 'l';
                funcLength = 2;
            }

            if (funcLength > 0) {
                (*tokens)[*tokenCount].type = FUNCTION;
                (*tokens)[*tokenCount].value[0] = funcValue;
                (*tokens)[*tokenCount].value[1] = '\0';
                (*tokenCount)++;
                ptr += funcLength;
                continue;
            }

            while (isAlphabetic(*ptr) && funcLength < 31) {
                (*tokens)[*tokenCount].value[funcLength] = *ptr;
                funcLength++;
                ptr++;
            }
            (*tokens)[*tokenCount].value[funcLength] = '\0';
            (*tokenCount)++;
            continue;
        }
        ptr++;
    }
    return *tokenCount;
}

