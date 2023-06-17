#ifndef AISD_5_FIBONACCIHEAP_H
#define AISD_5_FIBONACCIHEAP_H

#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

struct FibNode {
    size_t key;
    bool marked;
    size_t degree;
    FibNode *b, *f, *p, *c;

    FibNode() {
        this->key = 0;
        this->marked = false;
        this->degree = 0;
        this->b = this->f = this->p = this->c = nullptr;
    }

    FibNode(size_t key) {
        this->key = key;
        this->marked = false;
        this->degree = 0;
        this->b = this->f = this->p = this->c = nullptr;
    }
};

class FibonacciHeap {
    FibNode *min;
    size_t N;

    bool isEmpty();

public:

    static size_t nComp;

    static inline void initComp() {
        nComp = 0;
    }

    FibonacciHeap();

    FibonacciHeap(FibNode *);

    void insert(FibNode *);

    void merge(FibonacciHeap *);

    FibNode *extractMin();
};

#endif //AISD_5_FIBONACCIHEAP_H
