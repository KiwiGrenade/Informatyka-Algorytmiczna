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
    for(size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        arr[i] = stol(line);
    }

    


    return 0;
}