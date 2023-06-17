#ifndef AISD_5_BINOMIALHEAP_H
#define AISD_5_BINOMIALHEAP_H

#include <iostream>

struct BinNode {
    size_t key;
    size_t degree;
    BinNode *f, *p, *c;

    BinNode() {
        this->key = 0;
        this->degree = 0;
        this->f = this->p = this->c = nullptr;
    }

    BinNode(size_t key) {
        this->key = key;
        this->degree = 0;
        this->f = this->p = this->c = nullptr;
    }
};

class BinomialHeap {
    BinNode *roots;
    BinNode *min;

    static void linkTrees(BinNode *, BinNode *);

    static BinNode *mergeRoots(BinomialHeap *, BinomialHeap *);

public:
    BinomialHeap();

    BinomialHeap(BinNode *);

    void insert(BinNode *);

    void merge(BinomialHeap *);

    BinNode *first();

    BinNode *extractMin();
};

#endif //AISD_5_BINOMIALHEAP_H
