//Jakub Jaskow L02Z01.c
#include <stdio.h>

int main()
{
    //inicjacja zmiennej "licznik" zerami
    int zlotowki = 0, grosze = 0, licznik [14] = {0}, i = 0;
    //inicjacja nominalow zlotowek
    int nominaly_zlotowek[8] = {200,100,50,20,10,5,2,1};
    //inicjacja nominalow groszy
    int nominaly_groszy[6] = {50,20,10,5,2,1};

    //wczytywanie liczb
    printf("podaj liczbe zlotych: \n");
    scanf("%d", &zlotowki);
    printf("podaj liczbe groszy: \n");
    scanf("%d", &grosze);

    //petla odpowiedzialna za rozklad ilosci nominalow zlotowek
    while (i < 8)
    {
        licznik[i] = licznik[i] + (zlotowki / nominaly_zlotowek[i]);
        zlotowki = zlotowki % nominaly_zlotowek[i];
    	i++;
    }

    //petla odpowiedzialna za rozklad ilosci nominalow groszy
    while (i < 14)
    {
        licznik[i] = licznik[i] + (grosze / nominaly_groszy[i-8]);
        grosze = grosze % nominaly_groszy[i-8];
    	i++;
    }
    //zmienna "i" jest zerowana poniewaz zostala zainicjowana w funkcji main
    i = 0;

    //drukowanie nominalow banknotow
    printf("banknoty:\n");
    while ( i < 8)
    {
        printf("%d x %d \n", licznik[i], nominaly_zlotowek[i]);
    	i++;
    }
    //drukowanie nominalow monet
    printf("monety\n");
    while (i < 14)
    {
        printf("%d x %d \n", licznik[i], nominaly_groszy[i-8]);
    	i++;
    }
    return 0;
}
