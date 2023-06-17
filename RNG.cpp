#include <iostream>
#include <chrono>
#include <random>
#include <unordered_set>
int main(int argc, char* argv[])
{
    size_t seed = std::chrono::system_clock::now().time_since_epoch().count();
    size_t n = std::stol(argv[1]);
    std::mt19937 generator (seed);
    std::uniform_int_distribution<> distribution (65, 90);

    std::vector<char> set;
    std::vector<char> set1;

    while(set.size() < n)
        set.push_back((char) distribution(generator));
    while(set1.size() < n)
        set1.push_back((char) distribution(generator));

    std::cout << n << std::endl;

    for (auto i : set)
        std::cout << i << std::endl;
    for (auto i : set1)
        std::cout << i << std::endl;
    return 0;
}
