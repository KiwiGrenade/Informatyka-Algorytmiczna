//main.c Jakub Jaskow
#include <stdio.h>
#include "func.h"
int main(void)
{
    char napis[] = "lol";
    if (palindrome(napis[]))
    {
        printf("Napis |%s| jest palindromem \n", napis[]);
    }
    else
    {
        printf("Napis |%s| nie jest palindromem \n", napis[]);
    }
    return 0;
}
