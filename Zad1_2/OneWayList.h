#ifndef UNTITLED_ONEWAYLIST_H
#define UNTITLED_ONEWAYLIST_H

struct Node
{
    int val;
    struct Node* link;
};

struct OneWayList
{
    struct Node* end;
    struct Node* start;
};

int getFromList(int index, struct OneWayList* list);
void merge(struct OneWayList* list1, struct OneWayList* list2);
#endif
