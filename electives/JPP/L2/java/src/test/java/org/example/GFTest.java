package org.example;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;
import java.util.Random;

class GFTest {
    private static final long p = 1234577;
    private static final long MIN_VAL = 1;
    private static final long MAX_VAL = p;
    //    private static final long TEST_RUNS = 100;
    private final Random random = new Random();

    @Test
    void Constructor() {
        long val = -3;
        GF A = new GF(p, val);
        GF B = new GF(p, p + val);
        assertEquals(A.getVal(), B.getVal());
        assertEquals(A.getP(), B.getP());
    }

    @Test
    void Getters() {
        GF A = new GF(p, 1);
        assertEquals(p, A.getP());

        A = new GF(p, p - 1);
        assertEquals(p - 1, A.getVal());
    }

    @Test
    void Setters() {
        GF t = new GF(1, 1);
        t.setP(p);
        assertEquals(p, t.getP());

        long val = 3;
        t = new GF(p, 1);
        t.setVal(val);
        assertEquals(val, t.getVal());
    }

    @Nested
    @DisplayName("TEST COMPARES")
    class TestCompares {
        GF L;
        GF R;
        long val;

        @BeforeEach
        void setupValues() {
            val = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
        }
        @Test
        void Equals() {
            L = new GF(p, val);
            R = new GF(p, val);
            assertTrue(GF.equals(L, R));
        }
        @Test
        void notEquals() {
            L = new GF(p, val);
            R = new GF(p, val - 1);
            assertTrue(GF.notEquals(L, R));
        }
        @Test
        void lessThan() {
            L = new GF(p, val - 1);
            R = new GF(p, val);
            assertTrue(GF.lessThan(L, R));
        }
        @Test
        void greaterThan() {
            L = new GF(p, val);
            R = new GF(p, val - 1);
            assertTrue(GF.greaterThan(L, R));
        }
        @Test
        void lessThanOrEqual() {
            L = new GF(p, val);
            R = new GF(p, val);
            assertTrue(GF.lessThanOrEqual(L, R));
            R = new GF(p, val + 1);
            assertTrue(GF.lessThanOrEqual(L, R));
        }
        @Test
        void greaterThanOrEqual() {
            L = new GF(p, val);
            R = new GF(p, val);
            assertTrue(GF.greaterThanOrEqual(L, R));
            R = new GF(p, val - 1);
            assertTrue(GF.greaterThanOrEqual(L, R));
        }
    }

    @Nested
    @DisplayName("TEST ARITHMETIC")
    class TestArithmetic {
        GF L;
        GF R;

        @Nested
        @DisplayName("TEST UNARY")
        class TestUnary {
            private long val;

            @BeforeEach
            void setupValue() {
                val = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
            }

            @Test
            void plus() {
                L = new GF(p, val);
                R = L.plus();
                assertEquals(R, L);
            }

            @Test
            void minus() {
                GF L = new GF(p, val);
                GF R = L.minus();
                assertEquals(R.getVal(), (p - L.getVal()) % p);
            }
        }

        @Nested
        @DisplayName("TEST BINARY")
        class TestBinary {
            private long val1;
            private long val2;
            GF C;

            @BeforeEach
            void setupValues() {
                val1 = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
                val2 = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
            }

            @Test
            void subtract() {
                L = new GF(p, val1);
                R = new GF(p, val2);
                C = GF.subtract(L, R);

                assertEquals(C.getVal(), GF.add(L, R.minus()).getVal());
            }

            @Test
            void add() {
                L = new GF(p, val1);
                R = new GF(p, val2);
                C = GF.add(L, R);

                long exp_res = (R.getVal() + L.getVal()) % p;
                assertEquals(C.getVal(), exp_res);
            }

            @Test
            void multiply() {
                L = new GF(p, val1);
                R = new GF(p, val2);
                C = GF.multiply(L, R);

                long exp_res = (R.getVal() * L.getVal()) % p;
                assertEquals(C.getVal(), exp_res);
            }

            @Test
            void divide() {
                L = new GF(p, val1);
                R = new GF(p, val2);
                C = GF.divide(L, R);

                long RValReverse = Lib.iLDES(R.getVal(), R.getP(), Lib.iGCD(R.getVal(), R.getP()))[0];
                long _val = (L.getVal() * RValReverse) % L.getP();
                assertEquals(C.getVal(), _val);
            }
        }
    }
    @Nested
    @DisplayName("TEST ASSIGNMENT")
    class TestAssignment {
        GF L;
        GF R;
        private long val1;
        private long val2;

        @BeforeEach
        void setupValues() {
            val1 = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
            val2 = random.nextLong(MAX_VAL - MIN_VAL) + MIN_VAL;
        }

        @Test
        void assign() {
            L = new GF(p, val1);
            R = new GF(p, val2);
            L.assign(R);

            assertEquals(L.getVal(), R.getVal());
            assertEquals(L.getP(), R.getP());
        }
        //FIXME: Fails
        @Test
        void plusAssign() {
            L = new GF(p, val1);
            R = new GF(p, val2);

            L.plusAssign(R);
            assertEquals(L.getVal(), GF.add(L, R).getVal());
        }
        //FIXME: Fails
        @Test
        void minusAssign() {
            L = new GF(p, val1);
            R = new GF(p, val2);

            L.minusAssign(R);
            assertEquals(L.getVal(), GF.subtract(L, R).getVal());
        }
        //FIXME: Fails
        @Test
        void multiplyAssign() {
            L = new GF(p, val1);
            R = new GF(p, val2);

            L.multiplyAssign(R);
            assertEquals(L.getVal(), GF.multiply(L, R).getVal());
        }

        @Test
        void divideAssign() {
            L = new GF(p, val1);
            R = new GF(p, val2);

            L.divideAssign(R);
            assertEquals(L.getVal(), GF.divide(L, R).getVal());
        }
    }
}