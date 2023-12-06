/*# Jakub Jaśków 268415*/
%{
#define YYSTYPE int
#include <iostream>
#include <string>
#define P 1234577

using namespace std;

extern int yylex();
extern int yyparse();
int yyerror(string s);

int toGP(int a, int G);

int euclidAlgo(int a, int G, int *x, int *y);
int invGP(int a, int G);
int divGP(long int a, int b, int G);

int powGP(long int a, int pow);

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
            cout << ONP << endl;
            cout << "= " << $1 << endl << endl; 
            ONP = "";
        }
    | error '\n' { 
            if (error_msg == "") 
                error_msg = "zła składnia";
            cout << "Błąd: " << error_msg << endl << endl; 
            ONP = ""; 
            error_msg = "";
        }
;

expr: 
    number                          { ONP += to_string($1) + " "; $$ = $1; }
    | '(' expr ')'                  { $$ = $2; }
    | '-' expr %prec NEG            { ONP += "~ "; $$ = toGP(-$2, P); }
    | expr '+' expr                 { ONP += "+ "; $$ = toGP($1 + $3, P); }
    | expr '-' expr                 { ONP += "- "; $$ = toGP($1 - $3, P); }
    | expr '*' expr                 { ONP += "* "; $$ = toGP($1 * $3, P); }
    | expr '^' exponent             { ONP += "^ "; $$ = toGP(powGP($1, toGP($3, P-1)), P); }
    | expr '/' expr { 
            ONP += "/ "; 
            int x,y;
            int r = euclidAlgo($3, P, &x, &y);
            if(r > 1) {
                error_msg = to_string($3) + " nie jest odwracalny w GF(" + to_string(P) + ")";
                YYERROR;
            } 
            else 
            {
                $$ = divGP($1, $3, P); 
            }
        }
;

exponent:
    exp_number                              { ONP += to_string($1) + " "; $$ = $1; }
    | '(' exponent ')'                      { $$ = $2; }
    | '-' exponent %prec NEG                { ONP += "~ "; $$ = toGP(-$2, P-1); }
    | exponent '+' exponent                 { ONP += "+ "; $$ = toGP($1 + $3, P-1); }
    | exponent '-' exponent                 { ONP += "- "; $$ = toGP($1 - $3, P-1); }
    | exponent '*' exponent                 { ONP += "* "; $$ = toGP($1 * $3, P-1); }
    | exponent '/' exponent { 
            ONP += "/ "; 
            int x,y;
            int r = euclidAlgo($3, P-1, &x, &y);
            if(r > 1) {
                error_msg = to_string($3) + " nie jest odwracalny w GF(" + to_string(P-1) + ")";
                YYERROR;
            } 
            else 
            {
                $$ = divGP($1, $3, P-1); 
            }
        }
;

number:
    NUM                     { $$ = toGP($1, P); }
    | '-' number %prec NEG  { $$ = toGP(-$2, P); }
;

exp_number:
    NUM                         { $$ = toGP($1, P-1) ; }
    | '-' exp_number %prec NEG  { $$ =  toGP(-$2, P-1); }

%%

int toGP(int a, int G) {
    return ((a % G) + G) % G;
}

int euclidAlgo(int a, int G, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return G;
    }
    int x1, y1;
    int d = euclidAlgo(G%a, a, &x1, &y1);
    *x = y1 - (G/a)*x1;
    *y = x1;
    return d;
}

int invGP(int a, int G) {
    int x, y;
    euclidAlgo(a, G, &x, &y);
    return toGP(x, G);
}

int divGP(long int a, int b, int G) {
    long int inv = invGP(b, G);
    return (int)((a*inv) % G);
}

int powGP(long int a, int pow) {
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
