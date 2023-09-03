//Jakub Jaskow L02Z04.c
#include <stdio.h>
#include <math.h>

//Poniewaz 1000! wykracza poza ramy zwyklych zmiennych dostepnych w jezyku c
//mozna zamienic silnie na logarytm, co skutkuje suma logarytmow o podstawach naturalnych
//wiemy tez, ze pierwiastek 1000 stopnia poddany logarytmowaniu dzieli sume logarytmow na 1000
//po czym sume mozna zamienic na spowrotem na postac nie logarytmiczna funkcja exp()
int main()
{
	//inicjacja zmiennych
	double log_suma = 0, wynik;
	//sumowanie logarytmow naturalnych od 1 do 1000
	for (double i = 1; i <= 1000; i++)
	{
		log_suma = log_suma + log(i);
	}

	//zamiana sumy na postac nie logarytmiczna oraz przypisanie tej wartosci zmiennej wynik
	wynik = exp(log_suma / 1000);
	printf("%f\n", wynik);
	return 0;
}
