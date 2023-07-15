#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

struct queue{
    void* key;
    Queue* next;
};

void queue_enqueue(Queue** q, void* data)
{
    Queue* newElem = static_cast<Queue *>(malloc(sizeof(*newElem)));
    *newElem = (Queue){.key = data, .next = NULL};
    if(*q == NULL) {
        *q = newElem;
        return;
    }
    Queue* cur = *q;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newElem;
}

void* queue_dequeue(Queue** q)
{
    if(*q == NULL)
        return NULL;
    void* data = (*q)->key;
    Queue* tmp = (*q)->next;
    free(*q);
    *q = tmp;
    return data;
}

bool queue_empty(Queue* q){
    if(q == NULL)
        return true;
    return false;
}

size_t queue_size(Queue* q){
    size_t size = 0;
    Queue* next = q;
    while (next != NULL){
        size++;
        next = next->next;
    }
    return size;
}

void* queue_front(Queue* q){
    return q->key;
}
