#include <random>
#include <stdexcept>
#include "DHSetup.hpp"

// FIXME: implement all things in GF
template<typename T>
class User {
private:
    static std::mt19937 rng;
    static std::uniform_int_distribution<uint32_t> dist;
    DHSetup<T>* DH;
    uint32_t secret = 0;
    T key;

    void keyException() {
        if(key == 0) {
            throw std::invalid_argument("Secret key has not been set! Do it with User<T>::setKey(T a).");
        }
    }

public:
    User(DHSetup<T>* _dh) {
        DH = _dh;
        secret = dist(rng);
        key = 0;
    }
    
    T getPublicKey() {
        return DH->power(DH->getGenerator(), secret);
    }

    void setKey(T a) {
        key = DH->power(a, secret);
    }

    T encrypt(T m) {
        keyException();
        return m * key;
    }

    T decrypt(T c) {
        keyException();
        return c / key; 
    }
};

template<typename T>
std::mt19937 User<T>::rng;

template<typename T>
std::uniform_int_distribution<uint32_t> User<T>::dist = std::uniform_int_distribution<uint32_t>();
