#include <iostream>
#include <random>
#include <list>
void printArr(size_t arr[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void printArrState(size_t arr[], size_t n) noexcept
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

size_t nSwap = 0;
size_t nComp = 0;

bool comp(size_t arr_j, size_t x)
{
    nComp++;
    return arr_j > x;
}

void insertionSort(size_t arr[], long p ,long r, long n)
{
    for(long i = p; i < r ;i++)
    {
        //j can be negative
        long j = i - 1;
        size_t x = arr[i];

        if(n < 40)
        {
            printArrState(arr, n);
        }
        for (; comp(arr[j], x) && j >= 0; nSwap++)
        {
            arr[j+1] = arr[j];
            j--;
            if(n < 40)
            {
                printArrState(arr, n);
            }
        }
        arr[j+1] = x;
    }
}

long partition(size_t arr[], long p, long r, long n) noexcept
{
    //i can be negatice
    long pivot = arr[r];
    long i = p - 1;
    for(long long j = p; j < r; j++)
    {
        nComp++;
        if(arr[j] <= pivot)
        {
            i++;
            nSwap++;
            std::swap(arr[i], arr[j]);
            if(n < 40)
            {
                printArrState(arr, n);
            }
        }
    }
    nSwap++;
    std::swap(arr[i+1], arr[r]);
    if(n < 40)
    {
        printArrState(arr, n);
    }
    return i+1;
}

void quickSort(size_t arr[], long p, long r, long n, long limit) noexcept
{
    if(p < r)
    {
        long long q = partition(arr, p, r, n);
        if(q - p < 5)
        {
            insertionSort(arr, p, q - 1, n);
            insertionSort(arr, q + 1, r, n);
        }
        quickSort(arr, p, q - 1, n, limit);
        quickSort(arr, q + 1, r, n, limit);
    }
}

int main(int argc, char* argv[])
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    size_t arr[n];
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        arr[i] = stol(line);
    }
    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printArr(arr, n);
    }

    quickSort(arr, 0, n - 1, n, std::stol(argv[1]));

    if(n < 40)
    {
        std::cout << std::endl << "Sorted array:" << std::endl;
        printArr(arr, n);
    }
    std::cout << "Number of comparisons: " << nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap << std::endl;
    std::cout << "Is array sorted: " << std::is_sorted(arr,arr+n-1) << std::endl;

    return 0;
}
