//
// Created by mango on 12.03.24.
//
#include "catch2/catch_test_macros.hpp"
#include "lib.h"
#include "iostream"

unsigned long long llrand() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

bool cmpPairs(struct int64_pair myResult1, struct int64_pair myResult2) {
    if ((myResult1.x == myResult2.x)
        && (myResult1.y == myResult2.y)) {
        return true;
    }
    else {
        std::cerr   << "myResult1.x = " << myResult1.x << std::endl
                    << "myResult2.x = " << myResult2.x << std::endl
                    << "myResult1.y = " << myResult1.y << std::endl
                    << "myResult2.y = " << myResult2.y << std::endl;
    }
    return false;
}

TEST_CASE( "Factorials are computed by iteration", "[IFactorial]" ) {
    REQUIRE( IFactor(0) == 1 );
    REQUIRE( IFactor(1) == 1 );
    REQUIRE( IFactor(2) == 2 );
    REQUIRE( IFactor(3) == 6 );
    REQUIRE( IFactor(10) == 3628800 );
}

TEST_CASE( "Factorials are computed by recursion", "[RFactorial]" ) {
    REQUIRE( RFactor(0) == 1 );
    REQUIRE( RFactor(1) == 1 );
    REQUIRE( RFactor(2) == 2 );
    REQUIRE( RFactor(3) == 6 );
    REQUIRE( RFactor(10) == 3628800 );
}


TEST_CASE( "Greatest common divisior is computed by iteration", "[IGCD]" ) {
    REQUIRE( IGCD(1, 1) == 1 );
    REQUIRE( IGCD(10, 100) == 10 );
}


TEST_CASE( "Greatest common divisior is computed by recursion", "[RGCD]" ) {
    REQUIRE( RGCD(1, 1) == 1 );
    REQUIRE( RGCD(10, 100) == 10 );
}

TEST_CASE( "IGCD ?= RGCD", "[IGCD/RGCD]" ) {
    uint64_t a, b;
    for(uint16_t i = 0; i < 20; i++) {
        a = llrand();
        b = llrand();
        REQUIRE( IGCD(a, b) == RGCD(a, b));
    }
}

TEST_CASE("Normal RLDES tests", "[RLDES]") {
    uint64_t a, b, c;
    struct int64_pair exp_out;

    a = 24;
    b = 36;
    c = 12;
    exp_out = {
        -1,
        1
    };
    REQUIRE(cmpPairs(RLDES(a, b, c), exp_out));

    a = 91;
    b = 35;
    c = 7;
    exp_out = {
        2,
        -5
    };
    REQUIRE(cmpPairs(RLDES(a, b, c), exp_out));
}


TEST_CASE("Normal ILDES tests", "[ILDES]") {
    uint64_t a, b, c;
    struct int64_pair exp_out;

    a = 24;
    b = 36;
    c = 12;
    exp_out = {
        -1,
        1
    };
    REQUIRE(cmpPairs(ILDES(a, b, c), exp_out));

    a = 91;
    b = 35;
    c = 7;
    exp_out = {
        2,
        -5
    };
    REQUIRE(cmpPairs(ILDES(a, b, c), exp_out));
}