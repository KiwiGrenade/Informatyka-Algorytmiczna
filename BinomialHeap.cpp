#include "BinomialHeap.h"
#include <list>

size_t BinomialHeap::nComp;

BinomialHeap::BinomialHeap() {
    this->trees = nullptr;
    this->min = nullptr;
}

BinomialHeap::BinomialHeap(BinNode *x) {
    this->trees = x;
    this->min = x;
}

void BinomialHeap::insert(BinNode *x) {
    this->merge(new BinomialHeap(x));
}

void BinomialHeap::linkTrees(BinNode *y, BinNode *z) {
    // Precondition: y -> key >= z -> key
    y->p = z;
    y->f = z->c;
    z->c = y;
    z->degree = z->degree + 1;
}

BinNode *BinomialHeap::mergeRoots(BinomialHeap *x, BinomialHeap *y) {
    BinNode *ret = new BinNode();
    BinNode *end = ret;

    BinNode *L = x->trees;
    BinNode *R = y->trees;
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    while (L != nullptr || R != nullptr) {
        if (L == nullptr) {
            end->f = R;
            end = end->f;
            R = R->f;
        } else if (R == nullptr) {
            end->f = L;
            end = end->f;
            L = L->f;
        } else {
            if (L->degree < R->degree) {
                end->f = L;
                end = end->f;
                L = L->f;
            } else {
                end->f = R;
                end = end->f;
                R = R->f;
            }
        }
    }
    return (ret->f);
}

void BinomialHeap::merge(BinomialHeap *bh) {
    BinomialHeap *H = new BinomialHeap();
    H->trees = mergeRoots(this, bh);

    if (H->trees == nullptr) {
        this->trees = nullptr;
        this->min = nullptr;
        return;
    }

    BinNode *prevX = nullptr;
    BinNode *x = H->trees;
    BinNode *nextX = x->f;
    while (nextX != nullptr) {
        if (x->degree != nextX->degree || (nextX->f != nullptr && nextX->f->degree == x->degree)) {
            prevX = x;
            x = nextX;
        } else if (x->key <= nextX->key) {
            nComp++;
            x->f = nextX->f;
            linkTrees(nextX, x);
        } else {
            nComp++;
            if (prevX == nullptr) H->trees = nextX;
            else prevX->f = nextX;
            linkTrees(x, nextX);
            x = nextX;
        }
        nextX = x->f;
    }

    this->trees = H->trees;
    this->min = H->trees;
    BinNode *cur = this->trees;
    while (cur != nullptr) {
        nComp++;
                if (cur->key < this->min->key)
            this->min = cur;
        cur = cur->f;
    }
}

BinNode *BinomialHeap::first() {
    return this->min;
}

BinNode *BinomialHeap::extractMin() {
    BinNode *ret = this->first();

    // delete ret from the list of trees
    BinNode *prevX = nullptr;
    BinNode *x = this->trees;
    while (x != ret) {
        prevX = x;
        x = x->f;
    }
    if (prevX == nullptr)
        this->trees = x->f;
    else prevX->f = x->f;

    // reverse the list of ret children
    BinNode *revChd = nullptr;
    BinNode *cur = ret->c;
    while (cur != nullptr) {
        BinNode *next = cur->f;
        cur->f = revChd;
        revChd = cur;
        cur = next;
    }

    // merge the two lists
    BinomialHeap *H = new BinomialHeap();
    H->trees = revChd;
    this->merge(H);

    return ret;
}

