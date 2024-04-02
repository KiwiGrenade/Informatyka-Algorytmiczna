//
// Created by mango on 12.03.24.
//
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include "wrapper.h"

unsigned long long llrand() {
    unsigned long long r = 0;

    for (int i = 0; i < 5; ++i) {
        r = (r << 15) | (rand() & 0x7FFF);
    }

    return r & 0xFFFFFFFFFFFFFFFFULL;
}

bool cmpPairs(struct int64Pair myResult1, struct int64Pair myResult2) {
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

TEST_CASE( "Factorials are computed by iteration", "[C_IFactorial]" ) {
    REQUIRE( C_IFactor(0) == 1 );
    REQUIRE( C_IFactor(1) == 1 );
    REQUIRE( C_IFactor(2) == 2 );
    REQUIRE( C_IFactor(3) == 6 );
    REQUIRE( C_IFactor(10) == 3628800 );
}

TEST_CASE( "Factorials are computed by recursion", "[C_RFactorial]" ) {
    REQUIRE( C_RFactor(0) == 1 );
    REQUIRE( C_RFactor(1) == 1 );
    REQUIRE( C_RFactor(2) == 2 );
    REQUIRE( C_RFactor(3) == 6 );
    REQUIRE( C_RFactor(10) == 3628800 );
}


TEST_CASE( "Greatest common divisior is computed by iteration", "[C_IGCD]" ) {
    REQUIRE( C_IGCD(1, 1) == 1 );
    REQUIRE( C_IGCD(10, 100) == 10 );
}


TEST_CASE( "Greatest common divisior is computed by recursion", "[C_RGCD]" ) {
    REQUIRE( C_RGCD(1, 1) == 1 );
    REQUIRE( C_RGCD(10, 100) == 10 );
}

TEST_CASE( "C_IGCD ?= C_RGCD", "[C_IGCD/C_RGCD]" ) {
    uint64_t a, b;
    for(uint16_t i = 0; i < 20; i++) {
        a = llrand();
        b = llrand();
        REQUIRE( C_IGCD(a, b) == C_RGCD(a, b));
    }
}

TEST_CASE("Normal ILDES tests", "[ILDES]") {
    uint64_t a, b, c;
    struct int64Pair exp_out;

    a = 24;
    b = 36;
    c = 12;
    exp_out = {
        -1,
        1
    };
    REQUIRE(cmpPairs(C_ILDES(a, b, c), exp_out));

    a = 91;
    b = 35;
    c = 7;
    exp_out = {
        2,
        -5
    };
    REQUIRE(cmpPairs(C_ILDES(a, b, c), exp_out));
}

TEST_CASE("Normal RLDES tests", "[RLDES]") {
    uint64_t a, b, c;
    struct int64Pair exp_out;

    a = 24;
    b = 36;
    c = 12;
    exp_out = {
        -1,
        1
    };
    REQUIRE(cmpPairs(C_RLDES(a, b, c), exp_out));

    a = 91;
    b = 35;
    c = 7;
    exp_out = {
        2,
        -5
    };
    REQUIRE(cmpPairs(C_RLDES(a, b, c), exp_out));
}
