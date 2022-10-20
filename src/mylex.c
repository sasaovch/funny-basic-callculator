#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylex.h"

void readNumber(char** value) {
    *value = malloc(sizeof(char));
    size_t size = 1;
    char value_chr;
    char* new_val;
    while ((value_chr = getchar()) != EOF) {
        if (value_chr >= '0' && value_chr <= '9') {
            new_val = malloc(size++);
            strcpy(new_val, *value);
            new_val[size - 2] = value_chr;
            free(*value);
            *value = new_val;
        } else {
            ungetc(value_chr, stdin);
            break;
        }
    }
}

int gettoken(char** curr_value) {
    char value;
    while ((value = getchar()) != EOF && value != '\n') {
        if (value == ' ' || value == '\t') {
            continue;
        } else if (value >= '0' && value <= '9') {
            ungetc(value, stdin);
            readNumber(curr_value);
            return TKN_NUM;
        } else if (value == '+') {
            *curr_value = malloc(sizeof(char));
            **curr_value = '1';
            return TKN_PLUS;
        } else if (value == '-') {
            *curr_value = malloc(sizeof(char));
            **curr_value = '1';
            return TKN_MINUS;
        } else if (value == '*') {
            *curr_value = malloc(sizeof(char));
            **curr_value = '2';
            return TKN_MUL;
        } else if (value == '/') {
            *curr_value = malloc(sizeof(char));
            **curr_value = '2';
            return TKN_DIV;
        } else if (value == '(') {
            *curr_value = malloc(sizeof(char));
            **curr_value = value;
            return TKN_LPAREN;
        } else if (value == ')') {
            *curr_value = malloc(sizeof(char));
            **curr_value = value;
            return TKN_RPAREN;
        } else {
            return TKN_ID;
        }
    }
    return TKN_EOF;
}

struct lexer_t* buildLexer()
{
    int type_token;
    char* curr_value = NULL;
    struct lexer_t* lexer = malloc(sizeof(struct lexer_t));
    do {
        type_token = gettoken(&curr_value);
        struct token_t* token = malloc(sizeof(struct token_t));
        token->type = type_token;
        token->value = curr_value;
        lexer->size++;
        lexer->token_array = realloc(lexer->token_array, lexer->size * sizeof(struct token_t));
        lexer->token_array[lexer->size - 1] = *token;
    } while (type_token != TKN_EOF);
    return lexer;
}
