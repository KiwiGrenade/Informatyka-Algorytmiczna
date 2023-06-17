#include "BinomialHeap.h"
#include <list>

size_t BinomialHeap::nComp;

BinomialHeap::BinomialHeap() {
    this->head = nullptr;
    this->min = nullptr;
}

BinomialHeap::BinomialHeap(BinNode *x) {
    this->head = x;
    this->min = x;
}

void BinomialHeap::insert(BinNode *x) {
    this->unionHeap(new BinomialHeap(x));
}

void BinomialHeap::linkTrees(BinNode *y, BinNode *z) {
    // Precondition: y -> key >= z -> key
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

BinNode *BinomialHeap::combineHeaps(BinomialHeap *x, BinomialHeap *y) {
    BinNode *ret = new BinNode();
    BinNode *end = ret;

    BinNode *L = x->head;
    BinNode *R = y->head;
    if (L == nullptr) return R;
    if (R == nullptr) return L;
    while (L != nullptr || R != nullptr) {
        if (L == nullptr) {
            end->sibling = R;
            end = end->sibling;
            R = R->sibling;
        } else if (R == nullptr) {
            end->sibling = L;
            end = end->sibling;
            L = L->sibling;
        } else {
            if (L->degree < R->degree) {
                end->sibling = L;
                end = end->sibling;
                L = L->sibling;
            } else {
                end->sibling = R;
                end = end->sibling;
                R = R->sibling;
            }
        }
    }
    return (ret->sibling);
}

void BinomialHeap::unionHeap(BinomialHeap *heap) {
    BinomialHeap *finalHeap = new BinomialHeap();
    finalHeap->head = combineHeaps(this, heap);

    // both heaps are empty - result is empty
    if (finalHeap->head == nullptr) {
        this->head = nullptr;
        this->min = nullptr;
        return;
    }

    // initialize pointers
    BinNode *prev = nullptr;
    BinNode *curr = finalHeap->head;
    BinNode *next = curr->sibling;

    // check four cases for
    while (next != nullptr) {
//        // go to another sibling
//        if(curr->degree != next->degree)
//        {
//            prev = curr;
//            curr = next;
//        }
        if (curr->degree != next->degree ||
            (next->sibling != nullptr && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            nComp++;
            curr->sibling = next->sibling;
            linkTrees(next, curr);
        } else {
            nComp++;
            if (prev == nullptr) finalHeap->head = next;
            else prev->sibling = next;
            linkTrees(curr, next);
            curr = next;
        }
        // go to another sibling
        next = curr->sibling;
    }

    this->head = finalHeap->head;
    this->min = finalHeap->head;
    BinNode *cur = this->head;
    while (cur != nullptr) {
        nComp++;
                if (cur->key < this->min->key)
            this->min = cur;
        cur = cur->sibling;
    }
}

BinNode *BinomialHeap::first() {
    return this->min;
}

BinNode *BinomialHeap::extractMin() {
    BinNode *ret = this->first();

    // delete ret from the list of head
    BinNode *prevX = nullptr;
    BinNode *x = this->head;
    while (x != ret) {
        prevX = x;
        x = x->sibling;
    }
    if (prevX == nullptr)
        this->head = x->sibling;
    else prevX->sibling = x->sibling;

    // reverse the list of ret children
    BinNode *revChd = nullptr;
    BinNode *cur = ret->child;
    while (cur != nullptr) {
        BinNode *next = cur->sibling;
        cur->sibling = revChd;
        revChd = cur;
        cur = next;
    }

    // unionHeap the two lists
    BinomialHeap *H = new BinomialHeap();
    H->head = revChd;
    this->unionHeap(H);

    return ret;
}

