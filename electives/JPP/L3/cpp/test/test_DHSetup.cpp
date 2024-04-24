#include <stdint.h>
#include <random>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "DHSetup.hpp"

TEST_CASE("DHSetup: p = 1234567891"){  
    // constexpr uint32_t testRuns = 100;
    constexpr uint32_t p = 1234567891;
    DHSetup<uint32_t> DH = DHSetup<uint32_t>(p);
    // constexpr uint32_t min_val = 0; 
    // constexpr uint32_t max_val = 100;
    constexpr uint32_t n_tests = 10;
    constexpr uint32_t min_val = 0; 
    SECTION("power()") { 
        constexpr uint32_t base_max_val = 5;
        constexpr uint32_t pow_max_val = 10;
        uint32_t a = GENERATE(take(n_tests, random(min_val, base_max_val)));
        uint32_t b = GENERATE(take(n_tests, random(min_val, pow_max_val)));
        CHECK(DH.power(a, b) == pow((long double)a,b));
    }
    // SECTION("getGenerator()") {
    //     
    // }
}
