#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "TwoWayList.h"
int main() {
    srand(time(NULL));
    struct TwoWayList
            *list1 = (struct TwoWayList*) malloc(sizeof (struct TwoWayList)),
            *list2 = (struct TwoWayList*) malloc(sizeof (struct TwoWayList));



    for (int i = 0; i < 10000; i++)
    {
        pushTWL(i, list1);
        pushTWL(i*2, list2);
    }

    double avgT = 0;
    for(int i = 1; i <= 9; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            clock_t start, end;
            start = clock();
            getFromTWL(1000*i, list1);
            end = clock();
            avgT += ((double) (end - start)) / CLOCKS_PER_SEC;
        }
        printf("Average time to access %d-th element: %lf\n", 1000 * i, avgT / 50);
        avgT = 0;
    }

    srand(time(NULL));
    avgT = 0;
    int randomNumber = rand() % 10000;
    for (int j = 0; j < 50; j++)
    {
        time_t start, end;
        start = clock();
        getFromTWL(randomNumber, list1);
        end = clock();
        avgT += ((double) (end - start)) / CLOCKS_PER_SEC;
    }
    printf("Average time to access %d: %lf\n", randomNumber, avgT/50);

    mergeTWL(list1, list2);

    for (int i = 0; i < 20; i++)
    {
        printf("%d\n",getFromTWL(i, list1)->val);
    }

    free(list1);
    free(list2);
    return 0;
}
