#include "math-lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readNumber(char **value) {
    *value = malloc(2);
    size_t size = 1;
    char *new_val;
    char c;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            new_val = malloc(++size);
            strcpy(new_val, *value);
            new_val[size - 2] = c;
            new_val[size - 1] = 0;
            free(*value);
            *value = new_val;
        } else {
            ungetc(c, stdin);
            return;
        }
    }
}

int gettoken(char **curr_value) {
    char value;
    while ((value = getchar()) != EOF && value != '\n') {
        if (value == ' ' || value == '\t') { continue; }
        if (value >= '0' && value <= '9') {
            ungetc(value, stdin);
            readNumber(curr_value);
            return TKN_NUM;
        }
        *curr_value = malloc(2);
        **curr_value = value;
        (*curr_value)[1] = '\0';
        if (value == '+') { return TKN_PLUS; }
        if (value == '-') { return TKN_MINUS; }
        if (value == '*') { return TKN_MUL; }
        if (value == '/') { return TKN_DIV; }
        if (value == '(') { return TKN_LPAREN; }
        if (value == ')') { return TKN_RPAREN; }
        return TKN_ID;
    }
    return TKN_EOF;
}

struct token *read_tokens() {
    size_t size = 0;
    struct token t = {0};
    struct token *tokens = NULL;
    do {
        t.type = gettoken(&t.value);
        size++;
        tokens = realloc(tokens, size * sizeof(struct token));
        tokens[size - 1] = t;
    } while (t.type != TKN_EOF);
    return tokens;
}