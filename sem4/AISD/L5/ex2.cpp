#include <iostream>
#include <cstring>
#include "FibonacciHeap.h"
#include "BinomialHeap.h"

int main(int argc, char *argv[]) {
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);

    size_t X[n];
    size_t Y[n];

    // initialize array X
    for (size_t i = 0; i < n; i++) {
        std::cin >> line;
        X[i] = std::stol(line);
    }
    // initialize array Y
    for (size_t i = 0; i < n; i++) {
        std::cin >> line;
        Y[i] = std::stol(line);
    }


    // Binomial Heap
    if (strcmp(argv[1], "bin") == 0) {
        // declare bh1 and bh2
        BinomialHeap *bh1 = new BinomialHeap();
        BinomialHeap *bh2 = new BinomialHeap();
        BinomialHeap::initComp();

        //initialize bh2 and bh2
        for (size_t i = 0; i < n; i++) {
            bh1->insert(new BinNode(X[i]));
            bh2->insert(new BinNode(Y[i]));
        }


        bh1->unionHeap(bh2);

        // extract all nodes from merged heap
        size_t arr[2 * n];
        for (size_t i = 0; i < 2 * n; i++) {
            arr[i] = bh1->extractMin()->key;
            if (n < 50) {
                std::cout << "Remove: " << arr[i] << std::endl;
            }
        }

        std::cout   << "Is array sorted: " << std::is_sorted(arr, arr + n) << std::endl
                    << "nComp: " << BinomialHeap::nComp << std::endl;

        delete bh1;
        delete bh2;
    }


    // Fibonacci Heap
    if (strcmp(argv[1], "fib") == 0) {

        // declare fh1 and fh2
        FibonacciHeap *fh1 = new FibonacciHeap();
        FibonacciHeap *fh2 = new FibonacciHeap();
        FibonacciHeap::initComp();

        // initialize fh1 and fh2
        for (size_t i = 0; i < n; i++) {
            fh1->insert(new FibNode(X[i]));
            fh2->insert(new FibNode(Y[i]));
        }


        // unionHeap fh1 to fh2
        fh1->merge(fh2);

        // extract all nodes from merged heap
        size_t arr[2 * n];
        for (size_t i = 0; i < 2 * n; i++) {
            arr[i] = fh1->extractMin()->key;
            if (n < 50) {
                std::cout << "Remove: " << arr[i] << std::endl;
            }
        }

        std::cout   << "Is array sorted: " << std::is_sorted(arr, arr + n) << std::endl
                    << "nComp: " << FibonacciHeap::nComp << std::endl;
        delete fh1;
        delete fh2;
    }

    return 0;
}