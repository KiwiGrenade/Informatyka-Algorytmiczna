#include <stddef.h>
#include "OneWayList.h"
int getFromList(int index, struct OneWayList* list)
{
    struct Node* temp;
    temp = list->start;
    for (int i = 0; i < index; i++)
    {
        temp = temp->link;
    }
    return temp->val;
}

void merge(struct OneWayList* list1, struct OneWayList* list2)
{
    list1->end->link = list2->start;
}