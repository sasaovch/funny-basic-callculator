#include "math-lex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum token_type gettoken(struct token *t) {
    char value;
    while ((value = getchar()) != EOF && value != '\n') {
        if (value == ' ' || value == '\t') { continue; }
        if (value >= '0' && value <= '9') {
            ungetc(value, stdin);
            scanf("%lf", &(t->tkn_value.num));
            return TKN_NUM;
        }
        t->tkn_value.val = NULL;
        if (value == '+') { return TKN_PLUS; }
        if (value == '-') { return TKN_MINUS; }
        if (value == '*') { return TKN_MUL; }
        if (value == '/') { return TKN_DIV; }
        if (value == '(') { return TKN_LPAREN; }
        if (value == ')') { return TKN_RPAREN; }
    }
    return TKN_END;
}

struct token *read_tokens() {
    size_t size = 0;
    struct token t = {0};
    struct token *tokens = NULL;
    do {
        t.type = gettoken(&t);
        size++;
        tokens = realloc(tokens, size * sizeof(struct token));
        tokens[size - 1] = t;
    } while (t.type != TKN_END);
    return tokens;
}