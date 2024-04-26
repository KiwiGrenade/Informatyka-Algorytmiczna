#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include "GF.hpp"
#include "lib.h"

#define MIN_VAL uint32_t(1)
#define MAX_VAL std::numeric_limits<uint32_t>::max()
#define TEST_RUNS 100
TEST_CASE("GF(1234577)") {

    uint32_t p = 1234577;
    uint32_t p2 = 1234567891;
    SECTION("custom") {
        uint32_t a = 1166403871;
        uint32_t exp = 327745170;
        GF A = GF(p2, a);
        A = A * A;
        GF EXP = GF(p2, exp);
        REQUIRE(A == EXP);
    }

    SECTION("constructor", "[GF][constructor]") {
        int64_t val = -3;
        GF A = GF(p, val);
        REQUIRE(A.getVal() == p + val);

        GF B = GF(p, val - 2*p);
        REQUIRE(B.getVal() == A.getVal());
    }

    SECTION("getters", "[GF][getters]") {
        SECTION("p") {
            GF A = GF(p, 1);
            REQUIRE(A.getP() == p);
        }
        SECTION("val") {
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
        SECTION("val") {
            uint32_t val = 3;
            GF t = GF(p, 1);
            t.setVal(val);
            REQUIRE(t.getVal() == val);
        }
    }

    // comparison operators
    SECTION("compare", "[GF][compare]") {
        uint32_t val = GENERATE(take(TEST_RUNS, random(MIN_VAL, MAX_VAL)));
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

    // assignment operators
    SECTION("assignment", "[GF][assignment]") {
        uint32_t val = GENERATE(take(TEST_RUNS, random(MIN_VAL, MAX_VAL)));
        GF T = GF(p, val);

        SECTION("operator =", "[GF][assignment][copy]") {
            GF tmp = T;
            REQUIRE(tmp == T);
        }

        GF tmp = T;

        SECTION("operator +=", "[GF][assignment][add]") {
            T+=T;
            REQUIRE(T == tmp+tmp);
        }
        SECTION("operator -=", "[GF][assignment][sub]") {
            T-=T;
            REQUIRE(T == tmp-tmp);
        }
        // SECTION("operator *=", "[GF][assignment][mul]") {
        //     T*=T;
        //     REQUIRE(T == tmp*tmp);
        // }
        SECTION("operator /=", "[GF][assignment][div]") {
            T/=T;
            REQUIRE(T == tmp/tmp);
        }
    }

    // arithmetic operators
    SECTION("arithmetic", "[GF][arithmetic]") {
        uint32_t val1 = GENERATE(take(TEST_RUNS, random(MIN_VAL, MAX_VAL)));
        SECTION("unary") {
            GF L = GF(p, val1);
            SECTION("operator +", "[GF][arithmetic][positive]") {
                GF R = +L;
                REQUIRE(R == L);
            }
            SECTION("operator -", "[GF][arithmetic][negative]") {
                GF R = -L;
                REQUIRE(R.getVal() == (p - L.getVal()));
            }
        }
        SECTION("binary") {
            uint32_t val2 = GENERATE(take(TEST_RUNS, random(MIN_VAL, MAX_VAL)));
            GF L = GF(p, val1);
            GF R = GF(p, val2);
            uint32_t exp_res;

            SECTION("operator +", "[GF][arithmetic][add]") {
                GF C = L + R;

                exp_res = (R.getVal() + L.getVal()) % p;

                REQUIRE(C.getVal() == exp_res);
            }
            SECTION("operator -", "[GF][arithmetic][sub]") {
                GF C = L - R;

                exp_res = (p + L.getVal() - R.getVal()) % p;

                REQUIRE(C.getVal() == exp_res);
            }
            // SECTION("operator *", "[GF][arithmetic][mul]") {
            //     GF C = L * R;
            //
            //     exp_res = (R.getVal() * L.getVal()) % p;
            //
            //     REQUIRE(C.getVal() == exp_res);
            // }
            SECTION("operator /", "[GF][arithmetic][mul]") {
                GF C = L / R;

                uint32_t ReversedRVal = ILDES((uint64_t) R.getVal(), (uint64_t)R.getP(), IGCD(R.getVal(), R.getP())).x;
                exp_res = (L.getVal() * ReversedRVal) % R.getP();

                REQUIRE(C.getVal() == exp_res);
            }
        }
    }
}


