//Jakub Jaskow L02Z05.c
#include <stdio.h>
//funkcja znajdudace najwiekszy wspolny dzielnik poprzez rekurencje
int NWD(int n, int m)
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

//funkcja zliczajaca liczbe par liczb wzglednie pierwszych w zakresie od 1 do n
double fi(double n)
{
    double licznik = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            //jezeli warunek bycia para liczb wzglednie pierwszych zostanie spelniony
            if (NWD(i,j) == 1)
            {
                //inkrementuj licznik
                licznik++;
            }
        }
    }
    return licznik;
}

int main()
{
    double x;
    for (double n = 1; n <= 1000; n++)
    {
        x = (fi(n)/(n*n));
        printf("%lf; %lf\n", n, x);
    }
    return 0;
}
