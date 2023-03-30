//
// Created by Grim Reaper on 30.03.2023.
//
#include <iostream>
#include <chrono>
#include <random>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    size_t n = std::stol(argv[1]);
    size_t arr[n];
    std::mt19937 generator (seed);

    for (size_t& i : arr)
    {
        i = generator();
    }
    std::sort(arr, arr + n, std::greater<>());

    for (size_t& i : arr)
    {
        std::cout << i << std::endl;
    }

    return 0;
}