%{
    #include <stdio.h>
    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }
%}

%token NUM
%token RET

%%

PR : EVALUATE
    | PR EVALUATE
    ;

EVALUATE: EXPR RET { printf("=%d\n", $$);}
        |  EXPR { printf("=%d\n", $$); }
        ;

EXPR:    TERM
        | EXPR '+' TERM { $$ = $1 + $3; }
        | EXPR '-' TERM { $$ = $1 - $3; }
;

TERM:    NUM
        | TERM '*' NUM  { $$ = $1 * $3; }
        | TERM '/' NUM  { $$ = $1 / $3; }
;

%%