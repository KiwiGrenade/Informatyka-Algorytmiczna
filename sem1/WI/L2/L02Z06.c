//Jakub Jaskow L02Z06.c
#include <stdio.h>

//funkcja wyliczajaca sume dzielnikow
int sigma(int n)
{
    //kazda liczba naturalna dodatnia jest podzielna przez 1
    int suma = 1;

    //zaczynamy iteracje od 2, poniewaz ^^
    for (int i = 2; i < n; i++)
    {
        if (n % i == 0)
        {
            //dodaj dzielnik do sumy
            suma += i;
        }
    }
    return suma;
}
int main()
{
    printf("Liczby doskonale mniejsze od 1000:\n");
    for (int i = 0; i < 1000; i++)
    {
        //jezeli suma dzielnikow i jest rowna i, to wtedy liczba jest doskonala
        if (sigma(i) == i)
        {
            printf("%d\n", i);
        }
    }

    // n < m, wiec m = 2 a n = 1
    for (int m = 2; m < 1000; m++)
    {
        for (int n = 1; n < m; n++)
        {
            if (sigma(n) == m && sigma(m) == n)
            {
                printf("Para liczb n = %d i m = %d jest zaprzyjazniona\n", n, m);
            }
        }
    }
    return 0;
}
