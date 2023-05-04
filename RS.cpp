//
// Created by mango on 04.05.23.
#include <iostream>
#include "RandomSelect.h"
int main(int argc, char* argv[])
{
    //k-th order
    std::size_t k = std::stol(argv[1]);
    std::string line;
    std::cin >> line;
    std::size_t n = std::stol(line);
    std::size_t A[n];

    //check K
    if(k < 1 || k > n)
    {
        std::cout << "Error: Parameter K should be from threshold: 1 =< k =< n" << std::endl;
        return -1;
    }


    std::cout << "Number we're looking for: " << k << std::endl;

    // initialize array
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        A[i] = stol(line);
    }

    RandomSelect::showResults(A, n, k);

    return 0;
}