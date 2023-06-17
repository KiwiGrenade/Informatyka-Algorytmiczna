#include <iostream>
#include <cstring>
#include "FibonacciHeap.h"
#include "BinomialHeap.h"

int main(int argc, char *argv[]) {
    std::string line;
    std::cin >> line;
    int n = std::stol(line);

    int X[n];
    int Y[n];

    // initialize array X
    for (int i = 0; i < n; i++) {
        std::cin >> line;
        X[i] = std::stol(line);
    }
    // initialize array Y
    for (int i = 0; i < n; i++) {
        std::cin >> line;
        Y[i] = std::stol(line);
    }
    if (strcmp(argv[1], "bin") == 0) {
        BinomialHeap *bh1 = new BinomialHeap();
        BinomialHeap *bh2 = new BinomialHeap();
        for (int i = 0; i < n; i++) {
            bh1->insert(new BinNode(X[i]));
            bh2->insert(new BinNode(Y[i]));
        }

        int arr[2 * n];

        bh1->merge(bh2);

        for (int i = 0; i < 2 * n; i++) {
            arr[i] = bh1->extractMin()->key;
            std::cout << "Remove: " << arr[i] << std::endl;
        }

        std::cout << "Is array sorted: " << std::is_sorted(arr, arr + n) << std::endl;

        delete bh1;
        delete bh2;
    }
    if (strcmp(argv[1], "fib") == 0) {

        // declare fh1 and fh2
        FibonacciHeap *fh1 = new FibonacciHeap();
        FibonacciHeap *fh2 = new FibonacciHeap();

        // initialize fh1 and fh2
        for (int i = 0; i < n; i++) {
            fh1->insert(new FibNode(X[i]));
            fh2->insert(new FibNode(Y[i]));
        }


        // merge fh1 to fh2
        fh1->merge(fh2);

        // delete fh1
        int arr[2 * n];
        for (int i = 0; i < 2 * n; i++) {
            arr[i] = fh1->extractMin()->key;
            std::cout << "Remove: " << arr[i] << std::endl;
        }

        std::cout << "Is array sorted: " << std::is_sorted(arr, arr + 2 * n) << std::endl;

        delete fh1;
        delete fh2;
    }

    return 0;
}