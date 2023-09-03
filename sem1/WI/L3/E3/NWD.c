#include <stio.h>
#include "headers.h"

//funkcja znajdudace najwiekszy wspolny dzielnik poprzez rekurencje
long int NWD(long int n, long int m)
{
    //warunek zatrzymania rekurencji
    if (m == 0)
    {
        return n;
    }
    //w przeciwnym wypadku
    else
    return NWD(m, n%m);
}
