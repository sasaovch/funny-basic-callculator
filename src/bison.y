%{
    #include <stdio.h>
	#include <stdlib.h>
	extern int yylex();
	extern int convert_string_to_base_n();

    void yyerror(char *s) {
      fprintf (stderr, "%s\n", s);
    }
%}

%union {
    double num;
	char*  integer;
    char   id;
}

%token INT
%token NUM
%token RET

%type <integer> INT

%type <num> NUM
%type <num> NUMBER
%type <num> TERM
%type <num> EXPR
%type <num> EVAL

%%

EVAL	: EXPR RET { printf("%lf\n", $$); return 0; }
        | EXPR { printf("%lf\n", $$); return 0; }
        ;

EXPR	: TERM
        | EXPR '+' TERM { $$ = $1 + $3; }
        | EXPR '-' TERM { $$ = $1 - $3; }
		;

TERM	: NUMBER 
		| TERM '*' NUMBER { $$ = $1 * $3; }
        | TERM '/' NUMBER { $$ = $1 / $3; }
		;

NUMBER  : NUM
		| INT '_' INT 
		{ 
			unsigned long res;
			convert_string_to_base_n($1, atoi($3), &res);
			$$ = (double) res;
		}
		| INT { $$ = strtod($1, NULL); }
		;
%%
