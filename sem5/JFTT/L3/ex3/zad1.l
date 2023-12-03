%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "zad1y.hpp"
#define P 1234577

extern int yylex();
%}


%%
[ \t]  ;
^#(.|\\\n)*\n ;
\\\n   ;
[[:digit:]]+ { 
    yylval = atoi(yytext); 
    return NUM; 
}
"(" {return '(';}
")" {return ')';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"^" {return '^';}
\n  {return '\n';}
"\\" {return EXTD;}
.   {return ERR;}
%%