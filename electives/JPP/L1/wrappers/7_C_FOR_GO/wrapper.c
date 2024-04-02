#include <stdlib.h>
#include <stdio.h>
#include "wrapper.h"

uint64_t C_IFactor(uint16_t n)
{
    return (uint64_t)IFactor((GoUint16) n);
}

uint64_t C_RFactor(uint16_t n)
{
    return (uint64_t)RFactor((GoUint16) n);
}

uint64_t C_IGCD(uint64_t a, uint64_t b)
{
    return (uint64_t)IGCD((GoUint64) a, (GoUint64) b);
}

uint64_t C_RGCD(uint64_t a, uint64_t b)
{
    return (uint64_t)RGCD((GoUint64) a, (GoUint64) b);
}

struct int64Pair C_ILDES(int64_t a, int64_t b, int64_t c)
{
    return ILDES((GoInt64) a, (GoInt64) b, (GoInt64) c);
}

struct int64Pair C_RLDES(int64_t a, int64_t b, int64_t c)
{
    return C_RLDES((GoInt64) a, (GoInt64) b, (GoInt64) c);
}

