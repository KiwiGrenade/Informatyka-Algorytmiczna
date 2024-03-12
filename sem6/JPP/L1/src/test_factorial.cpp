//
// Created by mango on 12.03.24.
//
#include <catch2/catch_test_macros.hpp>
#include "lib.h"

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