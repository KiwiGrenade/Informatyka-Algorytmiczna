//Jakub Jaskow L02Z02.c
#include <stdio.h>

int main()
{
	//inicjacja oraz wczytywanie liczby
	int n;
	printf("Podaj liczbe liczb:");
	scanf("%d", &n);
	double bufor = 0, suma = 0, wynik;

	//wpisywanie "n" liczby liczb
	printf("Wpisz %d liczb:\n", n);
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &bufor);
		//sumowanie liczb po kolei
		suma = suma + bufor;
	}

	//drukowanie wyniku ktory jest suma arytmetyczna "n" wpisanych liczb
	wynik = suma / n;
	printf("Wynik: %f\n", wynik);
	return 0;
}
