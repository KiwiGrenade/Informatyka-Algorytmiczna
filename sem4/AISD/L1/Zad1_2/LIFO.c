#include "OneWayList.h"
#include <stdio.h>
#include <malloc.h>

void pushLIFO (int val, struct OneWayList* queue, int isVerbose)
{
    struct Node* temp = (struct Node*) malloc (sizeof (struct Node));
    temp->val = val;
    if(queue->end == NULL)
    {
        queue->end = queue->start = temp;
    }
    else
    {
        temp->link = queue->start;
        queue->start = temp;
    }
    if(isVerbose == 0)
    {
        printf("Add element %d to LIFO\n", queue->start->val);
    }
}

void popLIFO (struct OneWayList* queue, int isVerbose)
{
    if(queue->start == NULL || queue->end == NULL)
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
        temp = queue->start;
        queue->start = queue->start->link;
        if(isVerbose == 0)
        {
            printf("Delete element %d from LIFO\n", temp->val);
        }
        free(temp);
    }
}