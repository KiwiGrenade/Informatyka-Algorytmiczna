#include "FibonacciHeap.h"

FibonacciHeap::FibonacciHeap() {
    this->min = nullptr;
    this->N = 0;
}

FibonacciHeap::FibonacciHeap(FibNode *n) {
    this->min = n;
    n->b = n->f = n;
    n->p = n->c = nullptr;

    this->N = 1;
}

bool FibonacciHeap::isEmpty() {
    return (this->min == nullptr);
}

void FibonacciHeap::insert(FibNode *n) {
    this->merge(new FibonacciHeap(n));
}

void FibonacciHeap::merge(FibonacciHeap *h) {
    this->N += h->N;
    if (h->isEmpty()) return;
    if (this->isEmpty()) {
        this->min = h->min;
        return;
    }
    FibNode *first1 = this->min;
    FibNode *last1 = this->min->b;
    FibNode *first2 = h->min;
    FibNode *last2 = h->min->b;
    first1->b = last2;
    last1->f = first2;
    first2->b = last1;
    last2->f = first1;
    if (h->min->key < this->min->key) this->min = h->min;
}

FibNode *FibonacciHeap::extractMin() {
    FibNode *ret = this->min;
    this->N = this->N - 1;

    if (ret->f == ret) {
        this->min = nullptr;
    } else {
        FibNode *prev = ret->b;
        FibNode *next = ret->f;
        prev->f = next;
        next->b = prev;
        this->min = next; // Not necessarily a minimum. This is for assisting with the merge w/ min's children.
    }

    if (ret->c != nullptr) {
        FibNode *firstChd = ret->c;
        FibNode *currChd = firstChd;

        do {
            currChd->p = nullptr;
            currChd = currChd->f;
        } while (currChd != firstChd);

        if (this->isEmpty()) {
            this->min = firstChd;
        } else {
            FibNode *first1 = this->min;
            FibNode *last1 = this->min->b;
            FibNode *first2 = firstChd;
            FibNode *last2 = firstChd->b;
            first1->b = last2;
            last1->f = first2;
            first2->b = last1;
            last2->f = first1;
        }
    }

    if (this->min != nullptr) {
        size_t maxAuxSize = 5 * (((size_t) log2(this->N + 1)) + 1);
        FibNode *aux[maxAuxSize + 1];
        for (size_t i = 0; i <= maxAuxSize; i++) aux[i] = nullptr;
        size_t maxDegree = 0;

        FibNode *curr = this->min;

        do {
            FibNode *next = curr->f;
            size_t deg = curr->degree;
            FibNode *P = curr;
            while (aux[deg] != nullptr) {
                FibNode *Q = aux[deg];
                aux[deg] = nullptr;

                if (P->key > Q->key) {
                    FibNode *tmp = P;
                    P = Q;
                    Q = tmp;
                }

                Q->p = P;
                if (P->c == nullptr) {
                    P->c = Q;
                    Q->b = Q->f = Q;
                } else {
                    FibNode *last = P->c->b;
                    last->f = Q;
                    Q->b = last;
                    P->c->b = Q;
                    Q->f = P->c;
                }

                deg++;
                P->degree = deg;
            }
            aux[deg] = P;
            if (deg > maxDegree) maxDegree = deg;
            curr = next;
        } while (curr != this->min);


        FibNode *previous = aux[maxDegree];
        this->min = previous;
        for (size_t i = 0; i <= maxDegree; i++) {
            if (aux[i] != nullptr) {
                previous->f = aux[i];
                aux[i]->b = previous;
                if (aux[i]->key < this->min->key) this->min = aux[i];
                previous = aux[i];
            }
        }

    }

    return ret;
}

