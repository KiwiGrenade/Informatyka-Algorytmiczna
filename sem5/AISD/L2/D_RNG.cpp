#include <iostream>
#include <chrono>
#include <random>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    size_t n = std::stol(argv[1]);
    size_t arr[n];
    std::mt19937 generator (seed);
    std::uniform_int_distribution<> distribution (1, 1000000);

    for (size_t& i : arr)
    {
        i = distribution(generator);
    }
    std::sort(arr, arr + n, std::greater<>());

    std::cout << n << std::endl;
    for (size_t& i : arr)
    {
        std::cout << i << std::endl;
    }

    return 0;
}