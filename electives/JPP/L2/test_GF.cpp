#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "GF.hpp"

TEST_CASE("getP()", "[GF][getters]") {
    int64_t p = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
    REQUIRE(GF(p, 1).getP() == p);
}

TEST_CASE("operator==", "[GF][compare]") {
    SECTION("random values") {
        int64_t p = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        int64_t val = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        GF* L = new GF(p, val);
        GF* R = new GF(p, val);
        REQUIRE((*L) == (*R));
    }
    SECTION("exceptions") {
        int64_t p = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        int64_t val = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        GF* L = new GF(p, val);
        GF* R = new GF(p-1, val);
        REQUIRE_THROWS((*L) == (*R));
    }
}

TEST_CASE("operator!=", "[GF][compare]") {
    SECTION("random values") {
        int64_t p = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        int64_t val = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        GF* L = new GF(p, val);
        GF* R = new GF(p, val-1);
        REQUIRE((*L) != (*R));
    }
    SECTION("exceptions") {
        int64_t p = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        int64_t val = GENERATE(take(5, random(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max())));
        GF* L = new GF(p, val);
        GF* R = new GF(p-1, val-1);
        REQUIRE_THROWS((*L) != (*R));
    }
}