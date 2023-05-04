#include <iostream>
#include "DSelect.h"
void showResults(std::size_t A[], std::size_t n, std::size_t k) {

    if(n < 50)
    {
        std::cout << "Number we're looking for: " << k << std::endl;

        std::cout << "Array before select: " << std::endl;
        DSelect::printArrState(A, n);
    }
    std::size_t stat = DSelect::select(A, 0, n - 1, k, n);
    if(n < 50)
    {
        std::cout << "Array after select: " << std::endl;
        DSelect::printArrState(A, n);
    }
    std::cout << "Found " << k << "-th statistic: " << stat << std::endl;
    std::nth_element(A, A+k-1, A+n);
    std::cout << "Should be: " << A[k-1] << std::endl;
    std::cout << "Number of swaps: " << DSelect::nSwap << std::endl;
    std::cout << "Number of comparisons: " << DSelect::nComp << std::endl;
}
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
    // initialize array
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        A[i] = stol(line);
    }

    showResults(A, n, k);

    return 0;
}