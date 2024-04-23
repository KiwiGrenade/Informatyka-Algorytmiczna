#include <random>
#include <stdexcept>
#include "DHSetup.hpp"

template<typename T>
class User {
private:
    std::mt19937 rng;
    std::uniform_int_distribution<uint32_t> dist;
    DHSetup DH;
    uint32_t secret;
    T key;

public:
    User(DHSetup& _DH) {
        DH = _DH;
        dist = 
            std::uniform_int_distribution<uint32_t> 
            (0, std::numeric_limits<uint32_t>::max());
        secret = dist(rng);
    }
    
    T getPublicKey() {
        DH.power(DH.getGenerator(), secret);
    }

    void setKey(T a) {
        DH.power(a, secret);
    }

    T encrypt(T m) {
        return m * key;
    }

    T decrypt(T c) {
        return c / key;
    }
};
