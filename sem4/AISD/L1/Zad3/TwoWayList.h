#ifndef UNTITLED_TWOWAYLIST_H
#define UNTITLED_TWOWAYLIST_H
#include <stdio.h>
struct TwoWayNode
{
    int val;
    struct TwoWayNode* prev;
    struct TwoWayNode* next;
};

struct TwoWayList
{
    struct TwoWayNode* start;
};

void pushTWL(int val, struct TwoWayList* list);
struct TwoWayNode* getFromTWL(int index, struct TwoWayList* list);
void mergeTWL(struct TwoWayList* list1, struct TwoWayList* list2);

#endif //UNTITLED_TWOWAYLIST_H
