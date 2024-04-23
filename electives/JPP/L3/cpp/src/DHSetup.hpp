#include <stdint.h> 
#include <random>
#include <vector>
#include <cmath>
template<typename T>
class DHSetup {
private:
    T g;
    // std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<T> dist;
    std::vector<T> primeFactors;
    bool isGenerator(const T& a, const T& _p) {
        //TODO: throwing if primeFactors aren't initialized
        for(T q : primeFactors) {
            if(a * (_p-1)/q == 1)
                return false;
        }
        return true;
    }

    void TrialDivision(T n) {
        T f;
        f = 2;
        while (n % 2 == 0) { primeFactors.push_back(f); n /= 2; }
        f = 3;
        while (n % 3 == 0) { primeFactors.push_back(f); n /= 3; }
        f = 5;
        T ac = 9, temp = 16;
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
   DHSetup(const T _p) {
        dist = std::uniform_int_distribution<T> ((T) 1, _p);
        rng = std::mt19937();
        TrialDivision(_p - 1); 

        do {g = dist(rng);}
        while(isGenerator(g, _p-1) == false);
    }

    T getGenerator() {
        return g;
    }

    T power(T a, unsigned long b) {
        T res = (T) 1;
        while(b > 0) {
            if(b % 2 == 1) {
                res = res * a;
            }
            b /= 2; // b /= 2
            a *= a;
        }
        return res;
    }
};
