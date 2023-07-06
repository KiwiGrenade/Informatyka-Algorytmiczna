#ifndef UNTITLED_FIFO_H
#define UNTITLED_FIFO_H
#include "OneWayList.h"

void pushFIFO(int val, struct OneWayList* queue, int isVerbose);
void popFIFO(struct OneWayList* queue, int isVerbose);
#endif //UNTITLED_FIFO_H
