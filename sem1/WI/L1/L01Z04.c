//Jakub Jaskow L01Z04.c
#include <stdio.h>

int main()
{
    int n;
    printf("Wpisz liczbe:");
    scanf("%d", &n);
    
    //zapewnianie n liczby wierszy
    for (int i = 0; i < n; i++)
    {
        //drukowanie w wierszu odpowiedniej ilosci znakow spacji, im pozniejszy wiersz tym mniej znakow
        for (int x = 0; x < n - i; x++)
        {
            printf(" ");
        }
        
        //drukowanie asteriskow; aby trojkat byl rownoramienny ilosc gwiazdek w kazdym wierszu musi byc nieparzysta - stad (2 * i + 1)
        for (int j = 0; j < (2 * i + 1); j++)
        {
            printf("*");
        }
        //zmiana wiersza
        printf("\n");
    }
    return 0;
}
