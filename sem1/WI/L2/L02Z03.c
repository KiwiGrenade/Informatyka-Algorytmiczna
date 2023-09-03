//Jakub Jaskow L02Z03.c
#include <stdio.h>
int main()
{
	//zainicjuj i w funkcji main zamiast petli for aby wydrukowac wartosc
	//zmiennej i po zakonczeniu petli
	double suma = 0,i;
	
	//petla sumujaca kolejne wyrazy ciagu 1/n dopoki suma tych wyrazow
	//nie bedzie rowna lub wieksza od 10
	for (i = 1; suma < 10; i++)
	{
		suma = suma + (1 / i);
	}
	printf("N = %f\n", i);

	return 0;
}
