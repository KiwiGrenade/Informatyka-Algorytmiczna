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

void BinomialHeap::combineTrees(BinNode *y, BinNode *z) {
    // Precondition: y -> key >= z -> key
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

BinNode *BinomialHeap::combineHeaps(BinomialHeap *x, BinomialHeap *y) {
    // temporary nodes for merging heads
    BinNode *temp1 = new BinNode();
    BinNode *temp2 = temp1;

    //initialize roots of both heads
    BinNode *root1 = x->head;
    BinNode *root2 = y->head;

    // root1 == null -> return root2
    if (root1 == nullptr)
        return root2;
    // root2 == null -> return root1
    if (root2 == nullptr)
        return root1;

    // combine roots to make new increasing heap
    while (root1 != nullptr || root2 != nullptr) {
        if (root1 == nullptr) {
            temp2->sibling = root2;
            temp2 = temp2->sibling;
            root2 = root2->sibling;
        } else if (root2 == nullptr) {
            temp2->sibling = root1;
            temp2 = temp2->sibling;
            root1 = root1->sibling;
        } else {
            if (root1->degree < root2->degree) {
                temp2->sibling = root1;
                temp2 = temp2->sibling;
                root1 = root1->sibling;
            } else {
                temp2->sibling = root2;
                temp2 = temp2->sibling;
                root2 = root2->sibling;
            }
        }
    }
    return (temp1->sibling);
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
        // case 1 - curr.deg == next.deg
        if (curr->degree != next->degree) {
            prev = curr;
            curr = next;
        }
            // case 2 - curr.deg == next.deg == next.sibling.deg
        else if (curr->degree == next->degree &&
                 next->sibling != nullptr &&
                 next->sibling->degree == curr->degree) {

            prev = curr;
            curr = next;
        }
            // case 3
        else if (curr->key <= next->key) {
            nComp++;
            curr->sibling = next->sibling;
            combineTrees(next, curr);
        }
            // case 4
        else {
            nComp++;
            if (prev == nullptr)
                finalHeap->head = next;
            else
                prev->sibling = next;
            combineTrees(curr, next);
            curr = next;
        }
        // go to another sibling
        next = curr->sibling;
    }
    this->head = finalHeap->head;
    // Update minimum node
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
    // minimumNode
    BinNode *minNode = this->first();

    // delete minNode from the list of head
    BinNode *prev = nullptr;
    BinNode *curr = this->head;
    while (curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }
    // prev is null -> starting node is minimum
    // update head to sibling of head
    if (prev == nullptr)
        this->head = curr->sibling;
        // remove minimum node from heap
    else
        prev->sibling = curr->sibling;

    // reverse the list of minNode children
    BinNode *reverseNode = nullptr;
    BinNode *curr2 = minNode->child;
    while (curr2 != nullptr) {
        BinNode *next = curr2->sibling;
        curr2->sibling = reverseNode;
        reverseNode = curr2;
        curr2 = next;
    }

    // merge origin heap with the one containing children of minNode
    BinomialHeap *H = new BinomialHeap();
    H->head = reverseNode;
    this->unionHeap(H);

    return minNode;
}

