#ifndef AISD_5_BINOMIALHEAP_H
#define AISD_5_BINOMIALHEAP_H

#include <iostream>

struct BinNode {
    size_t key;
    size_t degree;
    BinNode *sibling, *parent, *child;

    BinNode() {
        this->key = 0;
        this->degree = 0;
        this->sibling = this->parent = this->child = nullptr;
    }

    BinNode(size_t key) {
        this->key = key;
        this->degree = 0;
        this->sibling = this->parent = this->child = nullptr;
    }
};

class BinomialHeap {
    // points to leftmost tree
    BinNode *head;
    // points to node with smallest value
    BinNode *min;

    static void combineTrees(BinNode *y, BinNode *z);

    static BinNode *combineHeaps(BinomialHeap *x, BinomialHeap *y);

public:

    static size_t nComp;

    static inline void initComp() {
        nComp = 0;
    }

    BinomialHeap();

    BinomialHeap(BinNode *);

    void insert(BinNode *);

    void unionHeap(BinomialHeap *heap);

    BinNode *first();

    BinNode *extractMin();
};

#endif //AISD_5_BINOMIALHEAP_H
