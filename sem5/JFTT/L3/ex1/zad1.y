/*Jakub Jaśków 268416*/

%{
#define YYSTYPE int
#include <iostream>
#include <string>
#define P 1234577

using namespace std;

extern int yylex();
extern int yyparse();
int yyerror(string s);

int GF_numConv(int a, int G);
int GF_sub(int a, int b, int G);
int GF_euclid_alg(int a, int b, int *x, int *y);
int GF_inv_num(int a, int G);
int GF_div(long int a, int b, int G);
int GF_pow(long int a, int pow);

string error_msg = "";
string ONP = "";
%}

%token NUM
%token ERR
%left '+' '-'
%left '*' '/'
%precedence NEG
%nonassoc '^'

%%

input:
    %empty
    | input line
;

line: 
    expr '\n' { 
            cout << "ONP: " << ONP << endl;
            cout << "= " << $1 << endl; 
            ONP = "";
        }
    | error '\n' { 
            if (error_msg == "") 
                error_msg = "zła składnia";
            cout << "Błąd: " << error_msg << endl; 
            ONP = ""; 
            error_msg = "";
        }
;

expr:
    number                          { ONP += to_string($1) + " "; $$ = $1; }
    | '(' expr ')'                  { $$ = $2; }
    | '-' '(' expr ')' %prec NEG    { ONP += "~ "; $$ = GF_numConv(-$3, P); }
    | expr '+' expr                 { ONP += "+ "; $$ = GF_numConv($1 + $3, P); }
    | expr '-' expr                 { ONP += "- "; $$ = GF_sub($1, $3, P); }
    | expr '*' expr                 { ONP += "* "; $$ = GF_numConv($1 * $3, P); }
    | expr '^' exponent             { ONP += to_string(GF_numConv($3, P)) + " ^ "; $$ = GF_pow($1, GF_numConv($3, P)); }
    | expr '/' expr { 
            ONP += "/ "; 
            int x, y;
            int r = GF_euclid_alg($3, P, &x, &y);
            if(r > 1) {
                error_msg = to_string($3) + " nie jest odwracalny w GF(" + to_string(P) + ")";
                YYERROR; 
            }
            else {
                $$ = GF_div($1, $3, P);
            }
        }
;

exponent:
    exponent_number                     { ONP += to_string($1) + " "; $$ = $1; }
    | '(' exponent ')'                  { $$ = $2; }
    | '-' '(' exponent ')' %prec NEG    { ONP += "~ "; $$ = GF_numConv(-$3, P-1); }
    | exponent '+' exponent             { ONP += "+ "; $$ = GF_numConv($1 + $3, P-1); }
    | exponent '-' exponent             { ONP += "- "; $$ = GF_numConv($1 - $3, P-1); }
    | exponent '*' exponent             { ONP += "* "; $$ = GF_numConv($1 * $3, P-1); }
    | exponent '/' exponent { 
        ONP += "/ "; 
            int x, y;
            int r = GF_euclid_alg($3, P-1, &x, &y);
            if(r > 1) {
                error_msg = to_string($3) + " nie jest odwracalny w GF(" + to_string(P-1) + ")";
                YYERROR; 
            }
            else {
                $$ = GF_div($1, $3, P-1);
            }
        }
;

number:
    NUM                     { $$ = $1; }
    | '-' number %prec NEG  { $$ = GF_numConv(-$2, P); }
;

exponent_number:
    NUM                     {$$ = $1; }
    | '-' number %prec NEG  {$$ = GF_numConv(-$2, P-1); }
;
%%

int GF_numConv(int a, int G) {
    return ((a % G) + G) % G;
}

int GF_sub(int a, int b, int G) {
    int val = (a-b) % G;
    if (val < 0)
        val += G;
    return val;
}

int GF_euclid_alg(int a, int G, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return G;
    }
    int x1, y1;
    int d = GF_euclid_alg(G%a, a, &x1, &y1);
    *x = y1 - (G/a)*x1;
    *y = x1;
    return d;
}

int GF_inv_num(int a, int G) {
    int x, y;
    GF_euclid_alg(a, G, &x, &y);
    return GF_numConv(x, G);
}

int GF_div(long int a, int b, int G) {
    long int inv = GF_inv_num(b, G);
    return (int)((a*inv) % G);
}

int GF_pow(long int a, int pow) {
    int result = a;
    if (pow == 0) {
        return 1;
    } 
    else if (pow == 1) {
        return a;
    }
    for(int i = 2; i <= pow; i++) {
        result = (result * a) % P;
    }
    return result;
}

int yyerror(string s) {	
    return 0;
}

int main()
{
    yyparse();
    return 0;
}