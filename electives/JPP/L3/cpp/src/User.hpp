#include <random>
#include <stdexcept>
#include "DHSetup.hpp"

template<typename T>
class User {
private:
    static std::mt19937 rng;
    static std::uniform_int_distribution<uint32_t> dist;
    DHSetup<T>* DH;
    uint32_t secret;
    T key;

public:
    User(DHSetup<T>* _dh) {
        DH = _dh;
        secret = dist(rng);
    }
    
    T getPublicKey() {
        return DH->power(DH->getGenerator(), secret);
    }

    void setKey(T a) {
        key = DH->power(a, secret);
    }

    T encrypt(T m) {
        return m * key;
    }

    T decrypt(T c) {
        return c / key;
    }
};

template<typename T>
std::mt19937 User<T>::rng;

template<typename T>
std::uniform_int_distribution<uint32_t> User<T>::dist = std::uniform_int_distribution<uint32_t>();
