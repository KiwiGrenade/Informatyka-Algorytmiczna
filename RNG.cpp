#include <iostream>
#include <chrono>
#include <random>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    size_t n = std::stol(argv[1]);
    std::uniform_int_distribution<> distribution (1, 1000000);

    std::cout << n << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cout << distribution(generator) << std::endl;
    }

    return 0;
}
