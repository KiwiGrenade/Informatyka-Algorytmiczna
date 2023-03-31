//
// Created by Grim Reaper on 30.03.2023.
//
#include <iostream>
#include <random>

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
    std::cout << std::endl << "RNG array:" << std::endl;
    for (size_t i : arr)
    {
        std::cout << i << std::endl;
    }

    for(size_t i = 1 ; i < n ;i++)
    {
        size_t j = i - 1;
        size_t x = arr[i];
        while(arr[j] > x && j > 0)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = x;
    }

    std::cout << std::endl << "Sorted array:" << std::endl;

    for(size_t &i : arr)
    {
        std::cout << i << std::endl;
    }


    return 0;
}