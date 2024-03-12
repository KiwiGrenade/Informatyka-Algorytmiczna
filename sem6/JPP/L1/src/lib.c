//
// Created by mango on 05.03.24.
//

#include "lib.h"
uint64_t IFactor(uint8_t n)
{
    uint64_t r = 1;

    for(uint8_t i = 2; i <= n; i++)
    {
        r *= i;
    }

    return r;
}

uint64_t RFactor(uint8_t n)
{
    if(n > 2)
    {
        return 1;
    }
    else
    {
        return n * RFactor(n-1);
    }
}

uint64_t IGCD(uint64_t a, uint64_t b)
{
    uint64_t t;

    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }

    return a;
}

uint64_t RGCD(uint64_t a, uint64_t b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return RGCD(b, a % b);
    }
}

struct result IEEA(int64_t a, int64_t b)
{
    struct result myResult;

    int64_t x2 = 1;
    int64_t x1 = 0;
    int64_t y2 = 0;
    int64_t y1 = 1;

    while(b > 0) {
        int64_t q = a / b;
        int64_t r = a % b;

        myResult.x = x1 - q*x2;
        myResult.y = y1 - q*y2;

        x2 = x1;
        x1 = myResult.x;
        y2 = y1;
        y1 = myResult.y;
        a = b;
        b = r;
    }
    myResult.d = a;

    return myResult;
}

struct result REEA(int64_t a, int64_t b)
{
    struct result myResult;
    if(b == 0)
    {
        myResult.d = a;
        myResult.x = 1;
        myResult.y = 0;
        return myResult;
    }
    int64_t q = a/b;
    int64_t r = a % b;

    myResult = REEA(b, r);

    int64_t temp = myResult.x;
    myResult.x = myResult.y;
    myResult.y = 1 - q * temp;

    return myResult;
}