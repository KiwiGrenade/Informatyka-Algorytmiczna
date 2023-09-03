#ifndef AISD_5_FIBONACCIHEAP_H
#define AISD_5_FIBONACCIHEAP_H

#include <iostream>
#include <cmath>


struct FibNode {
    size_t key;
    bool marked;
    size_t degree;
    FibNode *right, *left, *parent, *child;

    FibNode() {
        this->key = 0;
        this->marked = false;
        this->degree = 0;
        this->right = this->left = this->parent = this->child = nullptr;
    }

    FibNode(size_t key) {
        this->key = key;
        this->marked = false;
        this->degree = 0;
        this->right = this->left = this->parent = this->child = nullptr;
    }
};

class FibonacciHeap {
    FibNode *min;
    size_t nNodes;

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
