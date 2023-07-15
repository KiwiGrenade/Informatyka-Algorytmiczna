#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <unordered_set>

int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    size_t n = std::stol(argv[1]);
    std::mt19937 generator (seed);
    std::uniform_int_distribution<> distribution (1, 2 * n - 1);

    std::unordered_set<std::size_t> random;
    std::set<std::size_t, std::less<>> increasing;

    while(increasing.size() < n)
        increasing.emplace(distribution(generator));

    while(random.size() < n)
        random.emplace(distribution(generator));

    std::cout << n << std::endl;

    for (auto i : increasing)
        std::cout << i << std::endl;

    for(auto i : random)
        std::cout << i << std::endl;


    return 0;
}