#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "OneWayList.h"
#include "LIFO.h"
#include "FIFO.h"
int main()
{
    //ZAD 1
    struct OneWayList       *queue = (struct OneWayList*) malloc(sizeof (struct OneWayList)),
                            *list1 = (struct OneWayList*) malloc(sizeof (struct OneWayList)),
                            *list2 = (struct OneWayList*) malloc(sizeof (struct OneWayList));
    printf("Zad 1\n");
    printf("FIFO:\n");
    for(int i = 0; i < 100; i++)
    {
        pushFIFO(i, queue, 0);
    }
    for(int i = 0; i < 101; i++)
    {
        popFIFO(queue, 0);
    }
    printf("\n\nLIFO:\n");
    for(int i = 100; i < 200; i++)
    {
        pushLIFO(i, queue, 0);
    }
    for(int i = 100; i < 201; i++)
    {
        popLIFO(queue, 0);
    }
    free(queue);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //ZAD 2
    //initialize RNG
//    srand(time(NULL));
    printf("\n\nZad 2\n");
    for(int i = 0; i < 10000; i++)
    {
        pushLIFO(rand()%1000, list1, 1);
    }

    //////////////////////////////////////////////////////////////
    //random elements
    double avgT = 0;
    for(int i = 1; i <= 9; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            clock_t start, end;
            start = clock();
            getFromList(1000*i, list1);
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
        getFromList(randomNumber, list1);
        end = clock();
        avgT += ((double) (end - start)) / CLOCKS_PER_SEC;
    }
    printf("Average time to access %d: %lf\n", randomNumber, avgT/50);


    for(int i = 0 ; i < 100; i++)
    {
        pushLIFO(i, list2, 1);
    }

//    printf("%d\n",list1->end->val);
//    printf("%d\n",list2->start->val);

    merge(list1, list2);

    printf ("%d\n", getFromList(10060, list1));

    for(int i = 0; i < 100; i++)
    {
        popLIFO(list1, 1);
    }

    for(int i = 0; i < 10000; i++)
    {
        popLIFO(list2, 1);
    }

    free(list1);
    free(list2);


    return 0;
}
