#include <iostream>
#include <random>
#include "DSelect.h"

size_t DSelect::nComp = 0;
size_t DSelect::nSwap = 0;

void DSelect::printArrState(std::size_t arr[], std::size_t n) noexcept
{
    for (std::size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void DSelect::printArr(std::size_t arr[], std::size_t p, std::size_t r) noexcept
{
    for (std::size_t i = p; i < r; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool comp(size_t arr_j, size_t x)
{
    DSelect::nComp++;
    return arr_j > x;
}

void insertionSort(std::size_t A[], std::size_t p, std::size_t r)
{
    for(size_t i = 1 ; i < r-p ;i++)
    {
        //j can be negative
        long j = i - 1;
        size_t x = A[i];
        for (; comp(A[j], x) && j >= 0;DSelect::nSwap++)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

std::size_t DSelect::computeMedian(size_t A[], size_t p, size_t r)
{
    insertionSort(A, p, r);
    // A.len() is even -> choose the average of 2 values
    if((r-p) % 2 == 0)
    {
        unsigned short middle = std::floor((r+p-1)/2);
        return A[middle];
    }

    // A.len() is odd -> choose the middle point
    else
    {
        return A[(r + p) / 2];
    }
}

std::size_t DSelect::choosePivot(std::size_t A[], std::size_t p, std::size_t r)
{
    std::size_t nMedians = std::ceil((r-p+1)/5);
    std::size_t C[nMedians], k, i;

    //base case
    if(r-p < 10)
    {
        return computeMedian(A, p, r);
    }

    if((r-p+1) % 5 == 0)
    {
        for(i = 0, k = 0; i < nMedians; i++, k += 5)
        {
            C[i] = computeMedian(A, p+k, p+k+5);
        }
    }
    else
    {
        for(i = 0, k = 0; i < nMedians-1; i++, k += 5)
        {
            C[i] = computeMedian(A, p+k, p+k+5);
        }
        C[i] = computeMedian(A, p+k, p + k + (r-p+1) % 5);

    }

    return choosePivot(C,0,nMedians);
}

std::size_t DSelect::select(size_t A[], std::size_t p, std::size_t r, std::size_t i, std::size_t n)
{
    nComp++;
    if(p == r)
    {
        return A[p];
    }
    std::size_t q = std::distance(A, std::find(A + p, A + r, choosePivot(A, p, r)));
    q = partition(A, p, r, q, n);
    long k = q - p + 1;
    if (i == k)
    {
        nComp++;
        return A[q];
    }
    else if(i < k)
    {
        nComp++;
        return select(A, p, q - 1, i, n);
    }
    else
    {
        nComp++;
        return select(A, q + 1, r, i - k, n);
    }
}

std::size_t DSelect::partition(std::size_t A[], long p, long r, std::size_t q, std::size_t n) {
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
            DSelect::nSwap++;
            std::swap(A[i], A[j]);
        }
    }
    DSelect::nSwap++;
    std::swap(A[i + 1], A[r]);
    return i+1;
}
