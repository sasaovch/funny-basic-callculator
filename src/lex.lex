%{
	#include <stdlib.h>
	#include <stdio.h>
    #include "bison.tab.h"
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[a-f0-9]+		{
					yylval.integer = yytext;
					return INT;
				}
[0-9]+\.[0-9]+  { 
					yylval.num = strtod(yytext, NULL);
                  	return NUM;
                }
[ \t\r]         ; // whitespace
[\n]            { return RET; }
.				{ return *yytext; }

%%