%{
#include <stdio.h>

int yywrap();
int yylex();

int lines = 0;
int words = 0;
%}
    /*space or tab or \\n(backslash and new line)*/
WHITESPACE [[:blank:]]
%s NEWLINE
%x WORD
%x BLANKS
%%
    /*discard all whitespaces and new lines at the start file/new line*/
{WHITESPACE}|\n
<NEWLINE>. {
    printf("\n");
    /*call the second best rule:
    ABOVE -> you have encountered whitespaces;
    BELOW -> you have encountered a WORD*/
    REJECT;
}
. {
    /*if you read something that isn't a white space*/
    ECHO;
    words++;
    lines++;
    BEGIN(WORD);
}

<WORD>{
    [[:blank:]] BEGIN(BLANKS);
    \n BEGIN(NEWLINE);
}

<BLANKS>{
    /*delete all the whitespaces*/
    {WHITESPACE}
    
    \n BEGIN(NEWLINE);
    /*if you encounter something else than whitespace, print a space and THEN print the encounterd byte out*/
    . {
        printf(" ");
        ECHO;
        BEGIN(WORD);
        words++;
    }
}
%%

int yywrap() { 
    /* printf("\n"); */
    /* printf("line count: %d\n", lines); */
    /* printf("word count: %d\n", words); */
    return 1; 
} 
int main() { 
    return yylex(); 
}