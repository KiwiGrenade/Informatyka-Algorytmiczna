
#ifndef AISD_QUEUE_H
#define AISD_QUEUE_H

#include <stdbool.h>

typedef struct queue Queue;

void queue_enqueue(Queue** q, void* data);
void* queue_dequeue(Queue** q);
bool queue_empty(Queue* q);
size_t queue_size(Queue* q);
void* queue_front(Queue* q);

#endif //AISD_QUEUE_H
