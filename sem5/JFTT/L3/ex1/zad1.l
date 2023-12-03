/*Jakub Jaśków 268416*/
%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>
#include "zad1y.hpp"
#define P 1234577

extern int yylex();
%}


%%
    /*delete whitespace*/
[ \t]  ;
    /*delete # commets with or without \[enter] escapes*/
^#(.|\\\n)*\n ;
\\\n   ;
    /*convert digits to numbers in GF(P) (GF - Galois Field / Finite Field) */
[[:digit:]]+ { 
    yylval = atoi(yytext) % P; 
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
.   {return ERR;}
%%
