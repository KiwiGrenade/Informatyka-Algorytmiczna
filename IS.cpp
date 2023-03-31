//
// Created by Grim Reaper on 30.03.2023.
//
#include <iostream>
#include <random>

void printArr(size_t* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << *(arr+i) << std::endl;
    }
}

void printArrState(size_t* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << *(arr+i) << " ";
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

int main(int argc, char* argv[])
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


    for(size_t i = 1 ; i < n ;i++)
    {
        long j = i - 1;
        size_t x = arr[i];

        if(n < 40)
        {
            printArrState(arr, n);
        }
        while(comp(arr[j], x) && j >= 0)
        {
            arr[j+1] = arr[j];
            j--;
            if(n < 40)
            {
                printArrState(arr,n);
            }
        }
        //TODO check if nSwap is correct
        nSwap++;
        arr[j+1] = x;
    }

    std::cout << std::endl << "Sorted array:" << std::endl;

    if(n < 40)
    {
        printArr(arr, n);
    }
    std::cout << "Number of comparisons: " << nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap << std::endl;


    return 0;
}
