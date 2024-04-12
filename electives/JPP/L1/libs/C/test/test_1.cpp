//
// Created by mango on 12.03.24.
//
#include "catch2/catch_test_macros.hpp"
#include "lib.h"
#include "iostream"
#include "catch2/generators/catch_generators_adapters.hpp"
#include "catch2/generators/catch_generators_random.hpp"

#define MAX_VAL uint64_t(std::numeric_limits<uint64_t>::max())
#define MIN_VAL uint64_t(1)

TEST_CASE( "Factorials", "[Factorial]" ) {
    SECTION("Factorials are computed by iteration.", "[IFactor]") {
        REQUIRE( IFactor(0) == 1 );
        REQUIRE( IFactor(1) == 1 );
        REQUIRE( IFactor(2) == 2 );
        REQUIRE( IFactor(3) == 6 );
        REQUIRE( IFactor(10) == 3628800 );
    }
    SECTION("Factorials are computed by recursion", "[RFactor]") {
        REQUIRE( RFactor(0) == 1 );
        REQUIRE( RFactor(1) == 1 );
        REQUIRE( RFactor(2) == 2 );
        REQUIRE( RFactor(3) == 6 );
        REQUIRE( RFactor(10) == 3628800 );
    }
}


TEST_CASE("Greatest common divisor", "[GCD]") {
    SECTION( "Greatest common divisior is computed by iteration", "[IGCD]" ) {
        REQUIRE( IGCD(1, 1) == 1 );
        REQUIRE( IGCD(10, 100) == 10 );
    }
    SECTION( "Greatest common divisor is computed by recursion", "[RGCD]" ) {
        REQUIRE( RGCD(1, 1) == 1 );
        REQUIRE( RGCD(10, 100) == 10 );
    }
    SECTION( "IGCD ?= RGCD", "[IGCD/RGCD]" ) {
        uint64_t a = GENERATE(take(100, random(MIN_VAL, MAX_VAL)));
        uint64_t b = GENERATE(take(100, random(MIN_VAL, MAX_VAL)));
        REQUIRE( IGCD(a, b) == RGCD(a, b));
    }
}


TEST_CASE("TEST LDES", "[LDES]") {
    uint64_t a = GENERATE(take(100, random(MIN_VAL, MAX_VAL)));
    uint64_t b = GENERATE(take(100, random(MIN_VAL, MAX_VAL)));
    uint64_t c;
    struct int64_pair result{};

    SECTION("Normal RLDES tests", "[RLDES]") {
        c = RGCD(a, b);
        result = RLDES(a, b, c);
        REQUIRE(a*result.x + b*result.y == c);
    }

    SECTION("Normal ILDES tests", "[ILDES]") {
        c = IGCD(a, b);
        result = ILDES(a, b, c);
        REQUIRE(a*result.x + b*result.y == c);
    }
}
