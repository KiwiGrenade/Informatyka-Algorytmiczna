//
// Created by Grim Reaper on 30.03.2023.
//
#include <iostream>
#include <random>
#include <list>
void printList(std::list<size_t> &list) noexcept
{
    for (size_t i : list)
    {
        std::cout << i << std::endl;
    }
}

void printListState(std::list<size_t> &list) noexcept
{
    for (size_t i : list)
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

std::list<size_t> mergeSort(std::list<size_t> list) noexcept
{
    if(list.size() == 1)
    {
        return list;
    }
    size_t p = floor(list.size()/2);
    std::list<size_t> left, right;
    std::list<size_t>::iterator lit, pit;
    std::advance(lit, p);
    std::advance(pit, p+1);
    left.splice(left.begin(), list, list.begin(), lit);
    right.splice(right.begin(), list, list.begin(), pit);
    mergeSort(left);
    mergeSort(right);
    left.merge(right);
    return left;
}

int main(int argc, char* argv[])
{
    std::string line;
    std::cin >> line;
    size_t n = std::stol(line);
    std::list<size_t> list, sortedList;
    for (size_t i = 0; i < n; i++)
    {
        std::cin >> line;
        list.push_back(stol(line));
    }
    if(n < 40)
    {
        std::cout << "Random numbers:" << std::endl;
        printList(list);
    }

    sortedList = mergeSort(list);

    std::cout << std::endl << "Sorted array:" << std::endl;

    if(n < 40)
    {
        printList(sortedList);
    }
    std::cout << "Number of comparisons: " << nComp << std::endl;
    std::cout << "Number of swaps: " << nSwap << std::endl;


    return 0;
}
