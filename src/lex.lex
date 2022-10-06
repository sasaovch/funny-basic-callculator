%{
    #include "2.tab.h"
%}

%option yylineno
%option noyywrap

%%

[/][/].*\n      ; // comment
[0-9]+          { yylval = atoi(yytext);
                  return NUM;
                }
[ \t\r]      ; // whitespace
[\n]            {return RET;}
.              { return *yytext; }

%%