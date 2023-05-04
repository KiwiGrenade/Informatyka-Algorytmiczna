
#ifndef AISD_3_RANDOMSELECT_H
#define AISD_3_RANDOMSELECT_H

class RandomSelect{
public:
    static std::size_t nSwap;
    static std::size_t nComp;
    static long partition(std::size_t A[], long p, long r, long n) noexcept;

    static void showResults(size_t *A, size_t n, size_t k);

    static size_t randomSelect(size_t *A, size_t p, size_t r, const size_t i, size_t n);

    static long randomSelectPartition(size_t *A, long p, long r, size_t n);
};

#endif //AISD_3_RANDOMSELECT_H