#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "GF.hpp"

#define MIN std::numeric_limits<uint32_t>::min()
#define MAX std::numeric_limits<uint32_t>::max()

TEST_CASE("getters", "[GF][getters]") {
    uint32_t p = GENERATE(take(5, random(MIN, MAX)));
    SECTION("p") {
        GF A = GF(p, 1);
        REQUIRE(A.getP() == p);
    }
    SECTION("value") {
        GF A = GF(p, p-1);
        REQUIRE(A.getVal() == p-1);
    }
}

TEST_CASE("setters", "[GF][setters]") {
    SECTION("p") {
        GF t = GF(1, 1);
        uint32_t p = 3;
        t.setP(p);
        REQUIRE(t.getP() == p);
    }
    SECTION("value") {
        GF t = GF(1, 1);
        uint32_t val = 3;
        t.setVal(val);
        REQUIRE(t.getVal() == val);
    }
}

TEST_CASE("compare", "[GF][compare]") {
    uint32_t p = GENERATE(take(5, random(MIN, MAX)));
    uint32_t val = GENERATE(take(5, random(MIN, MAX)));
    SECTION("operator ==") {
        SECTION("positive") {
            GF L = GF(p, val);
            GF R = GF(p, val);
            REQUIRE(L == R);
        }
        SECTION("negative") {
            GF L = GF(p, val);
            GF R = GF(p, val-1);
            REQUIRE_FALSE(L == R);
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val);
            REQUIRE_THROWS(L == R);
        }
    }
    SECTION("operator !=") {
        SECTION("positive") {
            GF L = GF(p, val);
            GF R = GF(p, val - 1);
            REQUIRE(L != R);
        }
        SECTION("negative") {
            GF L = GF(p, val);
            GF R = GF(p, val - 1);
            REQUIRE(L != R);
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val-1);
            REQUIRE_THROWS(L != R);
        }
    }
    SECTION("operator <", "[GF][compare]") {
        SECTION("random values") {
            GF L = GF(p, val);
            GF R = GF(p, val+1);
            REQUIRE(L < R);
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val+1);
            REQUIRE_THROWS(L < R);
        }
    }
    SECTION("operator >", "[GF][compare]") {
        SECTION("random values") {
            GF L = GF(p, val);
            GF R = GF(p, val-1);
            REQUIRE(L > R);
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val-1);
            REQUIRE_THROWS(L > R);
        }
    }
    SECTION("operator <=", "[GF][compare]") {
        SECTION("random values") {
            SECTION("smaller") {
                GF L = GF(p, val);
                GF R = GF(p, val+1);
                REQUIRE(L <= R);
            }
            SECTION("equal") {
                GF L = GF(p, val);
                GF R = GF(p, val);
                REQUIRE(L <= R);
            }
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val-1);
            REQUIRE_THROWS(L <= R);
        }
    }
    SECTION("operator >=", "[GF][compare]") {
        SECTION("random values") {
            SECTION("smaller") {
                GF L = GF(p, val);
                GF R = GF(p, val-1);
                REQUIRE(L >= R);
            }
            SECTION("equal") {
                GF L = GF(p, val);
                GF R = GF(p, val);
                REQUIRE(L >= R);
            }
        }
        SECTION("exceptions") {
            GF L = GF(p, val);
            GF R = GF(p-1, val-1);
            REQUIRE_THROWS(L >= R);
        }
    }
}


TEST_CASE("operator =", "[GF][assignment][copy]") {
    uint32_t p = GENERATE(take(5, random(MIN, MAX)));
    uint32_t val = GENERATE(take(5, random(MIN, MAX)));

    GF L = GF(p, val);
    GF R = L;
    GF K = GF(1,1);
    K = R;

    REQUIRE(L == R);
    REQUIRE(K == R);
}

TEST_CASE("operator +", "[GF][arithmetic][add]") {
//        uint32_t p = GENERATE(take(5, random(MIN, MAX)));
//        uint32_t val2 = GENERATE(take(5, random(MIN, MAX)));
//        uint32_t val1 = GENERATE(take(5, random(MIN, MAX)));
        GF L = GF(20, 3);
        GF R = GF(20, 19);
        GF C = L + R;
        REQUIRE(C.getVal() == (R.getVal() + L.getVal()) % 20);
}