#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "User.hpp"
#include <random>
TEST_CASE("User: p = 1234567891"){
    constexpr uint32_t p = 1234567891;

    SECTION(""){
        DHSetup<uint32_t> DH = DHSetup<uint32_t>(p);
        User<uint32_t> user1 = User<uint32_t>(&DH);
        User<uint32_t> user2 = User<uint32_t>(&DH);
        REQUIRE(user1.getPublicKey() != user2.getPublicKey()); 
        REQUIRE_THROWS(user1.encrypt(1), user2.encrypt(1),
                        user1.decrypt(1), user2.decrypt(1));
        user1.setKey(user2.getPublicKey());
        user2.setKey(user1.getPublicKey());
        // user1.setKey(uint32_t(1));
        // user2.setKey(uint32_t(1));
        uint32_t message = 1;
        uint32_t encryptedMessage = user1.encrypt(message);
        uint32_t decryptedMessage = user2.decrypt(message);
        REQUIRE(decryptedMessage == message);
    }
};
