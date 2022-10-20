enum token {
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

struct token_t {
    enum token type;
    char* value;
};

struct lexer_t {
    size_t size;
    struct token_t* token_array;
};

struct lexer_t* buildLexer();