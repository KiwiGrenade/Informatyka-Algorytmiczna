#include "FibonacciHeap.h"

size_t FibonacciHeap::nComp;

FibonacciHeap::FibonacciHeap() {
    min = nullptr;
    nNodes = 0;
}

FibonacciHeap::FibonacciHeap(FibNode *n) {
    min = n;
    n->right = n->left = n;
    n->parent = n->child = nullptr;

    nNodes = 1;

}

void FibonacciHeap::insert(FibNode *n) {
    merge(new FibonacciHeap(n));
}

void FibonacciHeap::merge(FibonacciHeap *h) {
    nNodes += h->nNodes;
    if (h->min == nullptr)
        return;
    if (min == nullptr) {
        min = h->min;
        return;
    }
    FibNode *first1 = min;
    FibNode *last1 = min->right;
    FibNode *first2 = h->min;
    FibNode *last2 = h->min->right;
    first1->right = last2;
    last1->left = first2;
    first2->right = last1;
    last2->left = first1;
    nComp++;
    if (h->min->key < min->key)
        min = h->min;
}

FibNode *FibonacciHeap::extractMin() {
    // minimumNode
    FibNode *minNode = min;
    nNodes--;

    // minNode is nullptr
    if (minNode->left == minNode) {
        min = nullptr;
    } else {
        FibNode *prev = minNode->right;
        FibNode *next = minNode->left;
        prev->left = next;
        next->right = prev;
        min = next; // Not necessarily a minimum. This is for assisting with the unionHeap w/ min's children.
    }

    // minNode has children
    if (minNode->child != nullptr) {
        FibNode *firstChild = minNode->child;
        FibNode *currChild = firstChild;

        // set the parent of every minChild to nullptr
        do {
            currChild->parent = nullptr;
            currChild = currChild->left;
        }
        while (currChild != firstChild);

        // set the min as first(smallest) child
        if (min == nullptr) {
            min = firstChild;
        } else {
            FibNode *first1 = min;
            FibNode *last1 = min->right;
            FibNode *first2 = firstChild;
            FibNode *last2 = firstChild->right;
            first1->right = last2;
            last1->left = first2;
            first2->right = last1;
            last2->left = first1;
        }
    }

    if (min != nullptr) {
        size_t maxAuxSize = 5 * (((size_t) log2(nNodes + 1)) + 1);
        FibNode *aux[maxAuxSize + 1];
        for (size_t i = 0; i <= maxAuxSize; i++) aux[i] = nullptr;
        size_t maxDegree = 0;

        FibNode *curr = min;

        do {
            FibNode *next = curr->left;
            size_t deg = curr->degree;
            FibNode *P = curr;
            while (aux[deg] != nullptr) {
                FibNode *Q = aux[deg];
                aux[deg] = nullptr;

                nComp++;
                if (P->key > Q->key) {
                    FibNode *tmp = P;
                    P = Q;
                    Q = tmp;
                }

                Q->parent = P;
                if (P->child == nullptr) {
                    P->child = Q;
                    Q->right = Q->left = Q;
                } else {
                    FibNode *last = P->child->right;
                    last->left = Q;
                    Q->right = last;
                    P->child->right = Q;
                    Q->left = P->child;
                }

                deg++;
                P->degree = deg;
            }
            aux[deg] = P;
            if (deg > maxDegree) maxDegree = deg;
            curr = next;
        } while (curr != min);


        FibNode *previous = aux[maxDegree];
        min = previous;
        for (size_t i = 0; i <= maxDegree; i++) {
            if (aux[i] != nullptr) {
                previous->left = aux[i];
                aux[i]->right = previous;

                nComp++;
                if (aux[i]->key < min->key)
                    min = aux[i];
                previous = aux[i];
            }
        }

    }

    return minNode;
}

