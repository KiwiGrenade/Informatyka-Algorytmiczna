//
// Created by Grim Reaper on 30.03.2023.
//
#include <iostream>
#include <random>
#include <list>
void printList(const std::vector<size_t>& vec) noexcept
{
    for (size_t i : vec)
    {
        std::cout << i << std::endl;
    }
}

void printListState(const std::vector<size_t>& vec) noexcept
{
    for (size_t i : vec)
    {
        std::cout << i << " ";
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

//TODO
std::vector<size_t> merge(const std::vector<size_t>& left, const std::vector<size_t>& right) noexcept
{
    std::vector<size_t> merged;
    for (size_t i = 0; i < left.size(); i++)
    {
        if (left[i] < right[i])
    }
}

std::vector<size_t> mergeSort(std::vector<size_t> vec) noexcept
{
    if(vec.size() == 1)
    {
        return vec;
    }
    size_t p = floor(vec.size()/2);
    std::vector<size_t> left = std::vector<size_t>(vec.begin(), vec.begin() + p),
                        right= std::vector<size_t>(vec.begin() + p, vec.end()),
                        merged;
    //TODO Create custom merger that uses nSwaps and nComp
    std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(merged));
    left = mergeSort(left);
    right = mergeSort(right);
    return merge(left, right);
}

int main(int argc, char* argv[])
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    std::vector<size_t> vec;
    std::vector<size_t> sortedVec;
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        vec.push_back(stol(line));
    }
    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printList(vec);
    }

    sortedVec = mergeSort(vec);

    std::cout << std::endl << "Sorted array:" << std::endl;

    if(n < 40)
    {
        printList(sortedVec);
    }
    std::cout << "Number of comparisons: " << nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap << std::endl;


    return 0;
}
