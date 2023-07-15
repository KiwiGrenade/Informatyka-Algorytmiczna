#include "TwoWayList.h"
#include <malloc.h>
void pushTWL(int val, struct TwoWayList* list)
{
    struct TwoWayNode* temp = (struct TwoWayNode*)malloc (sizeof(struct TwoWayNode));
    temp->val = val;
    if(list->start == NULL)
    {
        list->start->next = list->start->prev = list->start = temp;
    }
    else
    {
        temp->next = list->start;
        temp->prev = list->start->prev;
        list->start->prev->next = temp;
        list->start->prev = temp;
        list->start = temp;
    }
}
struct TwoWayNode* getFromTWL(int index, struct TwoWayList* list)
{
    struct TwoWayNode* temp = list->start;
    for(int i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        printf("There is no such index in the list!\n");
    }
    return temp;
}
void mergeTWL(struct TwoWayList* list1, struct TwoWayList* list2)
{
    struct TwoWayNode *end1, *end2;
    //create false ends
    end1 = list1->start->prev;
    end2 = list2->start->prev;
    //let next node after the end be the starting node of different list
    end1->next = list2->start;
    end2->next = list1->start;
    //let node previous to the start node be the end node of different list
    list1->start->prev = end2;
    list2->start->prev = end1;
    list2->start = list1->start;
}