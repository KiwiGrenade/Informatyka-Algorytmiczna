//Jakub Jaskow L01Z01.c
#include <stdio.h>

int main()
{
    //wprowadzona zostaje zmienna "spacja" typu int ktora sluzy jaki licznik
    char zaklecie[11] = "ABRAKADABRA";
    int spacja = 0;
    
    //petla ogolna, sluzy do zmiany wiersza oraz kontrolowania ilosci znakow ktore zostana wyliczone przez nastepna petle for
    for (int i = 11; i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            printf("%c ", zaklecie[j]);
        }
        
        //zmienna spacja mowi nam ile znakow spacji ma poprzedzac "zaklece" w nastepnym wierszu
        spacja++;   
        //zmiana wiersza
        printf("\n");
        //drukowanie znakow spacji
        for (int x = 0; x < spacja; x++ )
        {
            printf(" ");
        }
    }
    return 0;
}
