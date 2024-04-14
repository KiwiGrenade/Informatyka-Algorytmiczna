package org.example;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import java.util.Random;

public class GFTest {
    private static final int MIN_VAL = 1;
    private static final int MAX_VAL = Integer.MAX_VALUE;
//    private static final int TEST_RUNS = 100;
    private static final int p = 1234577;
    private Random random = new Random();

    @Test
    public void testConstructor() {
        long val = -3;
        GF A = new GF(p, val);
        assertEquals(p + val, A.getVal());
    }

    @Test
    public void testGetters() {
        GF A = new GF(p, 1);
        assertEquals(p, A.getP());

        A = new GF(p, p-1);
        assertEquals(p-1, A.getVal());
    }

    @Test
    public void testSetters() {
        GF t = new GF(1, 1);
        t.setP(p);
        assertEquals(p, t.getP());

        int val = 3;
        t = new GF(p, 1);
        t.setVal(val);
        assertEquals(val, t.getVal());
    }

    // comparison operators
    @Test
    void testEquals() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val);
        assertTrue(L.equals(R));
    }
    @Test
    void notEquals() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val-1);
        R = new GF(p, val-1);
        assertTrue(L.notEquals(R));
    }
    @Test
    void lessThan() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val-1);
        GF R = new GF(p, val);
        assertTrue(L.lessThan(R));
    }
    @Test
    void greaterThan() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val-1);
        assertTrue(L.greaterThan(R));
    }
    @Test
    void lessThanOrEqual() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val);
        assertTrue(L.lessThanOrEqual(R));
        R = new GF(p, val+1);
        assertTrue(L.lessThanOrEqual(R));
    }
    @Test
    void greaterThanOrEqual() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val);
        assertTrue(L.greaterThanOrEqual(R));
        R = new GF(p, val-1);
        assertTrue(L.greaterThanOrEqual(R));
    }
    // arithmetic operators
    @Test
    public void plus() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);

        GF R = L.plus();
        assertEquals(R, L);
    }
    @Test
    public void minus() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);

        GF R = L.minus();
        assertEquals(R.getVal(), (p - L.getVal()) % p);
    }
    @Test
    public void subtract() {
        int val = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val);
        GF R = new GF(p, val);

        GF C = L.subtract(R);
        assertEquals(C.getVal(), 0);
    }
    @Test
    public void add() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        GF C = L.add(R);
        long exp_res = (R.getVal() + L.getVal()) % p;
        assertEquals(C.getVal(), exp_res);
    }
    @Test
    public void multiply() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        GF C = L.multiply(R);
        long exp_res = (R.getVal() * L.getVal()) % p;
        assertEquals(C.getVal(), exp_res);
    }
    @Test
    public void divide() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        GF C = L.divide(R);
        // The ILDES and IGCD methods are not implemented in this example
        // uint32_t ReversedRVal = ILDES((uint64_t) R.getVal
    }
    // assignment operators
    @Test
    public void plusEquals() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        L.plusEquals(R);
        assertEquals(L.getVal(), (val1 + val2) % p);
    }
    @Test
    public void minusEquals() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        L.minusEquals(R);
        assertEquals(L.getVal(), (p - val2) % p + val1);
    }
    //TODO: fix this
    @Test
    public void multiplyEquals() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        L.multiplyEquals(R);
        assertEquals(L.getVal(), (val1 * val2) % p);
    }
    @Test
    public void divideEquals() {
        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF L = new GF(p, val1);

        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
        GF R = new GF(p, val2);

        L.divideEquals(R);
        // The ILDES and IGCD methods are not implemented in this example
        // uint32_t ReversedRVal = ILDES((uint64_t) R.getVal(), (uint64_t)R.getP(), IGCD(R.getVal(), R.getP())).x;
        // assertEquals(L.getVal(), (val1 * ReversedRVal) % R.getP());
    }

//    @Test
//    public void testArithmetic() {
//        int val1 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
//        GF L = new GF(p, val1);
//
//        GF R = L.positive();
//        assertEquals(R, L);
//
//        R = L.negative();
//        assertEquals(R.getVal(), (p - L.getVal()));
//
//        int val2 = random.nextInt(MAX_VAL - MIN_VAL) + MIN_VAL;
//        L = new GF(p, val1);
//        R = new GF(p, val2);
//        int exp_res;
//
//        GF C = L.add(R);
//        exp_res = (R.getVal() + L.getVal()) % p;
//        assertEquals(C.getVal(), exp_res);
//
//        C = L.sub(R);
//        exp_res = (p + L.getVal() - R.getVal()) % p;
//        assertEquals(C.getVal(), exp_res);
//
//        C = L.mul(R);
//        exp_res = (R.getVal() * L.getVal()) % p;
//        assertEquals(C.getVal(), exp_res);
//
//        C = L.div(R);
//        // The ILDES and IGCD methods are not implemented in this example
//        // uint32_t ReversedRVal = ILDES((uint64_t) R.getVal(), (uint64_t)R.getP(), IGCD(R.getVal(), R.getP())).x;
//        // exp_res = (L.getVal() * ReversedRVal) % R.getP();
//        // assertEquals(C.getVal(), exp_res);
//    }
}
//
//
//
//    @Test
//    void plusEquals() {
//    }
//
//    @Test
//    void minusEquals() {
//    }
//
//    @Test
//    void multiplyEquals() {
//    }
//
//    @Test
//    void divideEquals() {
//    }
//}