#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "GF.hpp"
#include "lib.h"

#define MIN_VAL std::numeric_limits<uint32_t>::min()
#define MAX_VAL std::numeric_limits<uint32_t>::max()
//#define MIN_P uint32_t(1)
//#define MAX_P uint32_t(5)
//#define MAX_P std::numeric_limits<uint32_t>::max()
//#define MAX std::numeric_limits<uint32_t>::max()
//#define MIN std::numeric_limits<uint32_t>::min()

TEST_CASE("GF(1234577)"){
    uint32_t p = GENERATE(1234577);
    SECTION("getters", "[GF][getters]") {
        SECTION("p") {
            GF A = GF(p, 1);
            REQUIRE(A.getP() == p);
        }
        SECTION("value") {
            GF A = GF(p, p-1);
            REQUIRE(A.getVal() == p-1);
        }
    }
    SECTION("setters", "[GF][setters]") {
        SECTION("p") {
            GF t = GF(1, 1);
            t.setP(p);
            REQUIRE(t.getP() == p);
        }
        SECTION("value") {
            uint32_t val = 3;
            GF t = GF(p, 1);
            t.setVal(val);
            REQUIRE(t.getVal() == val);
        }
    }

    SECTION("compare", "[GF][compare]") {
//    uint32_t p = GENERATE(take(5, random(MIN_P, MAX_P)));
        uint32_t val = GENERATE(take(5, random(MIN_VAL, MAX_VAL)));
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
                GF L = GF(p, 1);
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
    SECTION("assignment", "[GF][assignment]") {

//    uint32_t p = GENERATE(take(5, random(MIN_P, MAX_P)));
        uint32_t val = GENERATE(take(5, random(MIN_VAL, MAX_VAL)));

        SECTION("operator =", "[GF][assignment][copy]") {

            GF L = GF(p, val);
            GF R = L;
            GF K = GF(1, 1);
            K = R;

            REQUIRE(L == R);
            REQUIRE(K == R);
        }
        SECTION("operator +=", "[GF][assignment][add]") {
            GF T = GF(p, val);
            T+=T;
            REQUIRE(T == T+T);
        }
        SECTION("operator -=", "[GF][assignment][sub]") {
            GF T = GF(p, val);
            T-=T;
            REQUIRE(T == T-T);
        }
        SECTION("operator *=", "[GF][assignment][mul]") {
            GF T = GF(p, val);
            T*=T;
            CHECK(T.getVal() == (T.getVal() * T.getVal()) % T.getP());
            CHECK(T.getP() == (T.getVal() * T.getVal()));
            REQUIRE(T.getVal() == (T*T).getVal());
        }
        SECTION("operator /=", "[GF][assignment][div]") {
            GF T = GF(p, val);
            T/=T;
            REQUIRE(T == T/T);
        }
    }
    SECTION("arithmetic", "[GF][arithmetic]") {
//    uint32_t p = GENERATE(take(5, random(MIN_P, MAX_P)));
        uint32_t val1 = GENERATE(take(5, random(MIN_VAL, MAX_VAL)));

        SECTION("unary") {
            SECTION("operator +", "[GF][arithmetic][positive]") {
                GF L = GF(p, val1);
                GF R = +L;
                REQUIRE(R == L);
            }
            SECTION("operator -", "[GF][arithmetic][negative]") {
                GF L = GF(p, val1);
                GF R = -L;
                REQUIRE(R.getVal() == (p - L.getVal()));
            }
        }
        SECTION("binary") {
            uint32_t val2 = GENERATE(take(5, random(MIN_VAL, MAX_VAL)));
            SECTION("operator +", "[GF][arithmetic][add]") {
                GF L = GF(p, val1);
                GF R = GF(p, val2);
                GF C = L + R;

                uint32_t exp_res = (R.getVal() + L.getVal()) % p;

                REQUIRE(C.getVal() == exp_res);
            }
//        SECTION("operator -", "[GF][arithmetic][sub]") {
//            GF L = GF(p, val1);
//            GF R = GF(p, val2);
//            GF C = L - R;
//
//            uint32_t exp_res = 19;
//
//            REQUIRE(C.getVal() == exp_res);
//        }
            SECTION("operator *", "[GF][arithmetic][mul]") {
                GF L = GF(p, val1);
                GF R = GF(p, val2);
                GF C = L * R;

                uint32_t exp_res = (R.getVal() * L.getVal()) % p;

                REQUIRE(C.getVal() == exp_res);
                REQUIRE(C == L * R);
            }
            SECTION("operator /", "[GF][arithmetic][mul]") {
                GF L = GF(p, val1);
                GF R = GF(p, val2);
                GF C = L / R;

                uint32_t ReversedRVal = ILDES((uint64_t) R.getVal(), (uint64_t)R.getP(), 1).x;
                uint32_t exp_res = L.getVal() * ReversedRVal;

                REQUIRE(C.getVal() == exp_res);
            }
        }
    }
}


