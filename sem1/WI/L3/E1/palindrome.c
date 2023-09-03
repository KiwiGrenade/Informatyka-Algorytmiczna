//palindrome.c Jakub Jaskow
#include <stdio.h>
#include <stdbool.h>
#include "func.h"

bool palindrome(char napis[])
{
    bool wynik = true;
    size_t len = strlen(napis);
    for (int i = 0; i < len; i++)
    {
        if (napis[i] != napis [len - i])
        {
            wynik = false; break;
        }
    }
    return wynik;
}
