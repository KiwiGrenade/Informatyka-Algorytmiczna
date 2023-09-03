#include "OneWayList.h"
#include <stdio.h>
#include <malloc.h>


void pushFIFO(int val, struct OneWayList* queue, int isVerbose)
{
    //create new Node
    struct Node* temp = (struct Node*) malloc(sizeof (struct Node));
    temp->val = val;
    //if OneWayList is empty
    if(queue->end == NULL)
    {
        queue->end = queue->start = temp;
    }
    else
    {
        queue->start->link = temp;
        queue->start = temp;
    }
    if(isVerbose == 0)
    {
        printf("Add element: %d to FIFO\n", queue->start->val);
    }
}

void popFIFO(struct OneWayList* queue, int isVerbose)
{
    if(queue->end == NULL)
    {
        if(isVerbose == 0)
        {
            printf("ERROR: Queue is empty!\n");
        }
        queue->end = queue->start = NULL;
    }
    else
    {
        struct Node* temp;
        temp = queue->end;
        queue->end = queue->end->link;
        if(isVerbose == 0)
        {
            printf("Delete element: %d from FIFO\n", temp->val);
        }
        free(temp);
    }
}