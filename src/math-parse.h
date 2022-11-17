enum token_type {
    TKN_ID,
    TKN_NUM,
    TKN_PLUS,
    TKN_MINUS,
    TKN_MUL,
    TKN_DIV,
    TKN_LPAREN,
    TKN_RPAREN,
    TKN_EOF,
};

struct token {
    enum token_type type;
    char *value;
};

double parse(struct token *tokens);