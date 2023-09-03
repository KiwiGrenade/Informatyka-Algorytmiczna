#include <stdio.h>
#include "headers.h"

int phi( long int n)
{
    int wynik = 0;
    for (int i = 1; i <= n ; i++)
    {
        if (NWD(n, i) == 1)
        wynik++;
    }
    return wynik;
}
