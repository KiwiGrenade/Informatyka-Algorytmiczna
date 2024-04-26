#include <random> 
#include <catch2/catch_test_macros.hpp> 
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "User.hpp"
#include "GF.hpp"

TEST_CASE("User: p = 1234567891"){
    constexpr uint32_t p = 1234567891; 
    constexpr uint32_t m = 20;
    GF message = GF(p, m);

    DHSetup<GF> DH = DHSetup<GF>(p);
    User<GF> user1 = User<GF>(&DH);
    User<GF> user2 = User<GF>(&DH);

    REQUIRE(user1.getPublicKey() != user2.getPublicKey()); 
    REQUIRE_THROWS(user1.encrypt(message), user2.encrypt(message),
                    user1.decrypt(message), user2.decrypt(message));

    user1.setKey(user2.getPublicKey());
    user2.setKey(user1.getPublicKey());
    
    GF encryptedMessage = user1.encrypt(message);
    GF decryptedMessage = user2.decrypt(encryptedMessage);
    
    REQUIRE(decryptedMessage == message);
};
