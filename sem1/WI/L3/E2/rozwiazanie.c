#include <stdio.h>
#include <math.h>
#include "headers.h"
double rozwiazanie (double a, double b, double eps)
{
    double m;
    while (abs(a - b) > eps)
    {
        m = (a + b) / 2.0;
        if (f(m) <= eps)
        {
            break;
        }
        else if ((f(a) * f(m)) < 0)
            b = m;
        else
            a = m;
    }
    double wynik = (a + b) / 2.0;
    return wynik;
}
