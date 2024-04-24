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
    }
};
