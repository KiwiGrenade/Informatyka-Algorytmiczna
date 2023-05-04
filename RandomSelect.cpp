#include <iostream>
#include <chrono>
#include <random>

std::size_t nComp = 0;
std::size_t nSwap = 0;

void printArrState(std::size_t arr[], std::size_t n) noexcept
{
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
long partition(std::size_t A[], long p, long r, long n) noexcept
{
    //i can be negatice
    long pivot = A[r];
    long i = p - 1;
    for(long long j = p; j < r; j++)
    {
        nComp++;
        if(A[j] <= pivot)
        {
            i++;
            nSwap++;
            std::swap(A[i], A[j]);
        }
    }
    nSwap++;
    std::swap(A[i + 1], A[r]);
    if(n < 50)
    {
        std::cout << "After selectPartition: " << std::endl;
        printArrState(A, n);
    }
    return i+1;
}
long randomSelectPartition(std::size_t A[], long p, long r, std::size_t n)
{

    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    std::uniform_int_distribution<> distribution (p, r);
    std::size_t i = distribution(generator);
    if(n < 50)
    {
        std::cout << std::endl  << "Selected pivot: " << A[i] << std::endl
                                << "Before selectPartition: " << std::endl;
        printArrState(A, n);
    }
    std::swap(A[i], A[r]);
    return partition(A, p, r, n);
}

std::size_t randomSelect(size_t A[], std::size_t p, std::size_t r, const std::size_t i, std::size_t n)
{
    nComp++;
    if(p == r)
    {
        return A[p];
    }
    long q = randomSelectPartition(A, p, r, n);
    long k = q - p + 1;
    if (i == k)
    {
        nComp++;
        return A[q];
    }
    else if(i < k)
    {
        nComp += 2;
        return randomSelect(A, p, q-1, i, n);
    }
    else
    {
        nComp += 2;
        return randomSelect(A,q+1, r,i-k, n);
    }
}

void showResults(std::size_t A[], std::size_t n, std::size_t k) {

    std::cout << "Array before select: " << std::endl;
    std::size_t stat = randomSelect(A, 0, n-1, k, n);
    if(n < 50)
    {
        std::cout << std::endl << std::endl << "Array after select: " << std::endl;
        printArrState(A, n);

    }
    std::cout << "Found " << k << "-th statistic: " << stat << std::endl;
    std::sort(A, A + n);
    std::cout << "Sorted array: " << std::endl;
    printArrState(A, n);
    std::cout << "Number of swaps: " << nSwap << std::endl;
    std::cout << "Number of comparisons: " << nComp << std::endl;

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


    std::cout << "Number we're looking for: " << k << std::endl;

    // initialize array
    for (std::size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        A[i] = stol(line);
    }

    showResults(A, n, k);

    return 0;
}

