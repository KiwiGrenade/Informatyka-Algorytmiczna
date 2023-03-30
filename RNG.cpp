#include <iostream>
#include <chrono>
#include <random>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    size_t n = std::stol(argv[1]);
    for (int i = 0; i < n; ++i)
    {
        std::cout << generator() << std::endl;
    }

    return 0;
}
