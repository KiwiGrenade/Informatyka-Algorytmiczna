%{
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

#define stack_size 100

int yylex();
int yywrap();

bool error = false;
int stack_ptr = -1;
int stack[stack_size];
bool stack_err = false; 

/*push to stack and retrieve*/
void push(int num) {
    stack_ptr++;
    if (stack_ptr < stack_size) {
        stack[stack_ptr] = num;
    } else {
        fprintf(stderr, "Whoops!");
        stack_err = true;
    } 
}

/*pop from stack and retrieve*/
int pop()  {
    if (stack_ptr >= 0) {
        stack_ptr--;
        return stack[stack_ptr + 1];
    } else {
        printf("Błąd zbyt mało argumentów.\n");
        stack_err = true;
        return 0;
    }
}

%}

%x ERROR

%%

    /*push a number*/
-?[0-9]+        push(atoi(yytext));

    /*addition*/
\+            {
                    push(pop()+pop());
                    if (stack_err) 
                        BEGIN(ERROR);
                }

    /*addition*/
\-             {
                    int a = pop();
                    int b = pop();
                    push(b - a);
                    if (stack_err) 
                        BEGIN(ERROR);
                }

    /*multiplication*/
\*             {
                    push(pop()*pop());
                    if (stack_err) 
                        BEGIN(ERROR);
                }

    /*division*/
\/             {
                    int divisor = pop();
                    if (divisor == 0) {
                        printf("Błąd: nie dziel przez 0!\n");
                        BEGIN(ERROR);
                    } else {
                        push(pop() / divisor);
                    }
                    if (stack_err) BEGIN(ERROR);
                }

    /*division with reminder*/
\%             {
                    int divisor = pop();
                    if (divisor == 0) {
                        printf("Błąd: nie dziel przez 0!\n");
                        BEGIN(ERROR);
                    } else {
                        push(pop() % divisor);
                    }
                    if (stack_err) BEGIN(ERROR);
                }
    
    /*power*/
\^             { 
    push( (int) pow((double) pop(), (double) pop()));
    }

    /*new line - next mathematical operation*/
\n            {       
                    if(!error){
                        if (stack_ptr == 0) {
                        printf("= %d\n", pop());
                    } else if(stack_ptr > 0 ){
                        printf("Błąd: zła ilość operatorów.\n");
                    }
                    } else {
                        printf("Za mało argumentów\n");
                        error = false;
                    }
                    stack_ptr = -1;
                    
                }

    /*check for not stated symbols*/
[^[:blank:]]    {printf("Błąd: zły symbol %s\n", yytext); error = true;};
    /*eat up whitespace*/
[[:blank:]]     ;

    /*error state*/
<ERROR>{
.*       ;
\n       {
                    stack_ptr = -1;
                    stack_err = false;
                    BEGIN(INITIAL);
                }
}

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}