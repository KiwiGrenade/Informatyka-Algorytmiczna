//
// Created by mango on 04.05.23.
//

#ifndef AISD_3_DSELECT_H
#define AISD_3_DSELECT_H

class DSelect
{
private:
    static std::size_t partition(std::size_t A[], long p, long r, std::size_t q, std::size_t n);
    static std::size_t computeMedian(std::size_t A[], std::size_t p, std::size_t r);

public:
    static std::size_t nComp;
    static std::size_t nSwap;

    static void printArr(std::size_t arr[], std::size_t p, std::size_t r) noexcept;
    static void printArrState(std::size_t arr[], std::size_t n) noexcept;

    static std::size_t select(std::size_t A[], std::size_t p, std::size_t r, std::size_t i, std::size_t n);

    static std::size_t choosePivot(std::size_t A[], std::size_t p, std::size_t r);

};

#endif //AISD_3_DSELECT_H
