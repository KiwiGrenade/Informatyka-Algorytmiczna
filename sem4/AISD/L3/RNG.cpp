#include <iostream>
#include <chrono>
#include <random>
#include <unordered_set>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    size_t n = std::stol(argv[1]);
    std::mt19937 generator (seed);
    std::uniform_int_distribution<> distribution (1, 2*n-1);

    std::unordered_set<std::size_t> set;


    while(set.size() < n)
    {
        set.emplace(distribution(generator));
    }

    std::cout << n << std::endl;

    for (auto i : set)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
