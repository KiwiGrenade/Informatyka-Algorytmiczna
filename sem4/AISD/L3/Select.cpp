#include <iostream>
#include "DSelect.h"
#include "RandomSelect.h"
int main(int argc, char* argv[])
{
    //k-th order
    std::size_t k = std::stol(argv[1]);
    std::string line;
    std::cin >> line;
    std::size_t n = std::stol(line);
    std::size_t A[n];
    std::size_t B[n];

    //check K
    if(k < 1 || k > n)
    {
        std::cout << "Error: Parameter K should be from threshold: 1 =< k =< n" << std::endl;
        return -1;
    }
    // initialize array
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        A[i] = stol(line);
    }
    for (std::size_t i = 0; i < n; i++)
    {
        B[i] = A[i];
    }

    DSelect::showResults(A, n, k);
    RandomSelect::showResults(B, n, k);
    return 0;
}