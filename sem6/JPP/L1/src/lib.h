#ifndef L1_LIB_H
#define L1_LIB_H
#include <stdint.h>

uint64_t IFactor(uint8_t n);
uint64_t RFactor(uint8_t n);

uint64_t IGCD(uint64_t a, uint64_t b);
uint64_t RGCD(uint64_t a, uint64_t b);

struct result IEEA(int64_t a, int64_t b);
struct result REEA(int64_t a, int64_t b);

struct result
{
    int64_t d;
    int64_t x;
    int64_t y;
};

#endif //L1_LIB_H