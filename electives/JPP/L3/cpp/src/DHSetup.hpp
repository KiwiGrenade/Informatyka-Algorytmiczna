#include <stdint.h> 
#include <random>
#include <vector>
#include <cmath>
#include <iostream>
#include "GF.hpp"
template<typename T>
class DHSetup {
private:
    T* g;
    static std::mt19937 rng;
    static std::uniform_int_distribution<uint32_t> dist;
    std::vector<uint32_t> primeFactors;
    
    bool isGenerator(const uint32_t& a, const uint32_t& _p) {
        for(uint32_t q : primeFactors) {
            if(a * (_p-1)/q == 1)
                return false;
        }
        return true;
    }

    void TrialDivision(uint32_t n) {
        uint32_t f;
        f = 2;
        while (n % 2 == 0) { primeFactors.push_back(f); n /= 2; }
        f = 3;
        while (n % 3 == 0) { primeFactors.push_back(f); n /= 3; }
        f = 5;
        uint32_t ac = 9, temp = 16;
        do {
            ac += temp; // Assume addition does not cause overflow with U type
            if (ac > n) break; 
            if (n % f == 0) {
                primeFactors.push_back(f);
                n /= f;
                ac -= temp;
            }
            else { 
                f += 2;
                temp += 8;
            }
        } while (1);
        if (n != 1) primeFactors.push_back(n);
    }
    
public: 
    DHSetup(const uint32_t _p) {
        dist = std::uniform_int_distribution<uint32_t> (1, _p);
        rng = std::mt19937();
        TrialDivision(_p - 1); 

        uint32_t tmp;
        do {tmp = dist(rng);}
        while(isGenerator(tmp, _p-1) == false);
        g = new GF(_p, tmp);
    }

    ~DHSetup(){
        free(g);
    }

    T getGenerator() {
        return *g;
    }

    T power(T a, unsigned long b) {
        T res = T(a.getP(), 1);
        for(int i = 0; b > 0; i++) {
            if(b & 1) {
                res *= a;
            }
            b >>= 1; // b /= 2
            a *= a;
        }
        std::cout << res << std::endl;
        return res;
    }
};
template<typename T>
std::mt19937 DHSetup<T>::rng;
template<typename T>
std::uniform_int_distribution<uint32_t> DHSetup<T>::dist;
 
