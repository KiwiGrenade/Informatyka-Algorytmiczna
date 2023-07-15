#include <iostream>
#include <random>
#include <list>

void printArr(size_t arr[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

void printArrState(size_t arr[], size_t n) noexcept {
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

void insertionSort(size_t arr[], long p, long r, size_t n)
{
    for(size_t i = 1 ; i < n ;i++)
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

int main()
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    size_t arr[n];
    for (size_t &i : arr)
    {
        std::cin >> line;
        i = stol(line);
    }

    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printArr(arr, n);
    }

    insertionSort(arr, 0, n-1, n);

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
