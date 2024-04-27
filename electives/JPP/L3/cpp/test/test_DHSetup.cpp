#include <stdint.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "DHSetup.hpp"
#include "GF.hpp"

TEST_CASE("DHSetup: p = 1234567891"){  
    constexpr uint32_t p = 1234567891;
    DHSetup<GF> DH = DHSetup<GF>(p);
    SECTION("power()") { 
        uint32_t a = 1166403871;
        uint32_t b = 581869302;
        CHECK(DH.power(GF(p, a), b)== GF(p, 724254047));
    }
}
