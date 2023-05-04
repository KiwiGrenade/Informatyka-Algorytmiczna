#include <iostream>
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

void arrState(std::size_t arr[], std::size_t p, std::size_t r) noexcept
{
    for (std::size_t i = p; i < r; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool comp(size_t arr_j, size_t x)
{
    nComp++;
    return arr_j > x;
}

void insertionSort(std::size_t A[], std::size_t p, std::size_t r)
{
    for(size_t i = 1 ; i < r-p ;i++)
    {
        //j can be negative
        long j = i - 1;
        size_t x = A[i];
        for (; comp(A[j], x) && j >= 0; nSwap++)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

long partition(std::size_t A[], long p, long r, std::size_t n) noexcept
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
long selectPartition(size_t A[], long p, long r, std::size_t q, std::size_t n)
{
    if(n < 50)
    {
        std::cout << std::endl  << "Selected pivot: " << A[q] << std::endl
                  << "Before selectPartition: " << std::endl;
        printArrState(A, n);
    }
    nSwap++;
    std::swap(A[q], A[r]);
    return partition(A, p, r, n);
}

std::size_t computeMedian(size_t A[], size_t p, size_t r)
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

std::size_t choosePivot(std::size_t A[], std::size_t p, std::size_t r)
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

std::size_t select(size_t A[], std::size_t p, std::size_t r, std::size_t i, std::size_t n)
{
    nComp++;
    if(p == r)
    {
        return A[p];
    }
    std::size_t q = std::distance(A, std::find(A + p, A + r, choosePivot(A, p, r)));
    q = selectPartition(A, p, r, q, n);
    long k = q - p + 1;
    if (i == k)
    {
        nComp++;
        return A[q];
    }
    else if(i < k)
    {
        nComp += 2;
        return select(A, p, q - 1, i, n);
    }
    else
    {
        nComp += 2;
        return select(A, q + 1, r, i - k, n);
    }
}

void showResults(std::size_t A[], std::size_t n, std::size_t k) {

    std::size_t stat = select(A, 0, n - 1, k, n);
    if(n < 50)
    {
        std::cout << std::endl << std::endl << "Array after select: " << std::endl;
        printArrState(A, n);
    }
    std::cout << "Found " << k << "-th statistic: " << stat << std::endl;
    std::nth_element(A, A+k-1, A+n);
    std::cout << "Should be: " << A[k-1] << std::endl;
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

