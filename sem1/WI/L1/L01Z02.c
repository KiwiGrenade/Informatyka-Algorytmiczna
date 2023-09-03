//Jakub Jaskow L01Z02.c
#include <stdio.h>

int main()
{
    float a, b, c, delta;
    printf("Wpisz 3 liczby rzeczywiste:\n");
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    printf("\n");
    
    //obliczanie delty
    delta = (b * b) - (4 * a * c);
    
    //jesli delta jest rowna zeru
    if(delta == 0)
    {
        //oblicz x
        float x;
        x = (-b) / (2 * a);
        printf("Istnieje jedno rozwiazanie: %f", x);
    }
    
    //jesli delta jest wieksza od  zera
    if(delta > 0)
    {
        //oblicz x1 oraz x2
        float x_1, x_2;
        x_1 = ((-b) - sqrt(delta)) / (2 * a);
        x_2 = ((-b) + sqrt(delta)) / (2 * a);
        printf("Istnieja dwa rozwiazania:\n");
        printf("x = %f oraz x = %f", x_1, x_2);
    }
    
    //inaczej
    else
    {
        printf("Nie ma w zbiorze liczb rzeczywistych rozwiazania.");
    }
    
    return 0;
}
