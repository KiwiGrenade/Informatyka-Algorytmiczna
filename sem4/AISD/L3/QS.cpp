#include <iostream>
#include <random>
#include <list>
#include "DSelect.h"

void printArr(size_t A[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << A[i] << std::endl;
    }
}

void printArrState(size_t A[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

size_t nSwap = 0;
size_t nComp = 0;

long partition(size_t A[], long p, long r, std::size_t q, long n) noexcept
{
    nSwap++;
    std::swap(A[q], A[r]);
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
            if(n < 40)
            {
                printArrState(A, n);
            }
        }
    }
    nSwap++;
    std::swap(A[i+1], A[r]);
    if(n < 40)
    {
        printArrState(A, n);
    }
    return i+1;
}

void quickSort(size_t A[], long p, long r, long n) noexcept
{
    if(p < r)
    {
        std::size_t pivotValue = DSelect::choosePivot(A, p, r);
        std::size_t q = std::distance(A, std::find(A + p, A + r, pivotValue));
        q = partition(A, p, r, q, n);
        quickSort(A, p, q - 1, n);
        quickSort(A, q + 1, r, n);
    }
}

int main(int argc, char* argv[])
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    size_t A[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        A[i] = stol(line);
    }
    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printArr(A, n);
    }

    quickSort(A, 0, n - 1, n);

    if(n < 40)
    {
        std::cout << std::endl << "Sorted array:" << std::endl;
        printArr(A, n);
    }
    std::cout << "Number of comparisons: " << nComp + DSelect::nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap + DSelect::nSwap << std::endl;
    std::cout << "Is array sorted: " << std::is_sorted(A,A+n-1) << std::endl;

    return 0;
}
