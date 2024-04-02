#ifdef __cplusplus
extern "C" {
#endif
#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdint.h>
#include "lib.h"

/*  
    I - iterative, R - recursive
    GCD - Greatest Common Divisor
    LDES - Linear Diophantine Equation Solver 
*/

uint64_t C_IFactor(uint16_t n);
uint64_t C_RFactor(uint16_t n);

uint64_t C_IGCD(uint64_t a, uint64_t b);
uint64_t C_RGCD(uint64_t a, uint64_t b);

struct int64Pair C_ILDES(int64_t a, int64_t b, int64_t c);
struct int64Pair C_RLDES(int64_t a, int64_t b, int64_t c);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //WRAPPER_H