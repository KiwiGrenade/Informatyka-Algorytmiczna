//Jakub Jaskow L01Z03.c
#include <stdio.h>

int main()
{
    int n;
    printf("Wpisz liczbe calkowita: ");
    scanf("%d", &n);
    
    //zapewnianie n wierszy prostokata
    for (int i = 0; i < n; i++)
    {
        //drukowanie n * 2 kolumn w wierszu
        for(int j = 0; j < n * 2; j ++)
        {
            printf("*");
        }
        //przejscie o wiersz nizej
        printf("\n");
    }
    return 0;
}
