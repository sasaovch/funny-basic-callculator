#pragma once
#define TOKEN_TYPE_COUNT 11

enum token_type {
    TKN_PLUS,
    TKN_MINUS,
    TKN_MUL,
    TKN_NUM,
    TKN_DIV,
    TKN_LPAREN,
    TKN_RPAREN,
    TKN_END,
    TKN_EXPR0,
    TKN_EXPR,
    TKN_TERM,
};

struct token {
    enum token_type type;
    union {
        char *val;
        double num;
    } tkn_value;
};

double parse(struct token *tokens);