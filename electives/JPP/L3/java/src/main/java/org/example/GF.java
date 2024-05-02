package org.example;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class GF {
    private long p;
    private long val;

    public GF(long _p, long _val) {
        if(_p <= 0) {
            throw new IllegalArgumentException("[GF]ERROR: p must be > 0");
        }
        p = _p;
        setVal(_val);
    }

    public long getP() {
        return p;
    }

    public void setP(long _p) {
        p = _p;
        setVal(val);
    }

    public long getVal() {
        return val;
    }

    public void setVal(long _val) {
        if(_val < 0 ) {
            val = inverse(p, val);
        }
        else {
            val = _val;
        }
    }

    private static void checkP(@NotNull GF L, @NotNull GF R) {
        if(L.p != R.p)
            throw new IllegalArgumentException("[GF]ERROR: not matching p!");
    }
   
    private static long inverse(long _p, long _val){ 
        return _p + (_val % _p);
    }

    // compare
    static public boolean equals(GF L, GF R) {
        checkP(L, R);
        return L.val == R.val;
    }
    static public boolean notEquals(GF L, GF R) {
        return !equals(L, R);
    }
    static public boolean lessThan(GF L, GF R) {
        checkP(L, R);
        return L.val < R.val;
    }
    static public boolean greaterThan(GF L, GF R) {
        return lessThan(R, L);
    }
    static public boolean lessThanOrEqual(GF L, GF R) {
        return !greaterThan(L, R);
    }
    static public boolean greaterThanOrEqual(GF L, GF R) {
        return !lessThan(L, R);
    }

    // arithmetic
    public GF plus() {
        return this;
    }
    public GF minus() {
        return new GF(this.p, (this.p - this.val) % this.p);
    }
    @NotNull
    static public GF subtract(GF L, GF R) {
        checkP(L, R);
        R = R.minus();
        long _val = (L.val + R.val) % L.p;
        return new GF(R.p, _val);
    }
    @NotNull
    @Contract("_, _ -> new")
    static public GF add(GF L, GF R) {
        checkP(L, R);
        long _val = (L.val + R.val) % L.p;
        return new GF(R.p, _val);
    }
    @NotNull
    @Contract("_, _ -> new")
    static public GF multiply(GF L, GF R) {
        checkP(L, R);
        long _val = (L.val * R.val) % L.p;
        return new GF(L.p, _val);
    }
    @NotNull
    @Contract("_, _ -> new")
    static public GF divide(GF L, GF R) {
        checkP(L, R);
        long RValReverse = Lib.iLDES(R.val, R.p, Lib.iGCD(R.val, R.p))[0];
        long _val = (L.val * RValReverse) % L.p;
        return new GF(L.p, _val);
    }

    // assign
    public void assign(@org.jetbrains.annotations.NotNull GF other) {
        setP(other.p);
        setVal(other.val);
    }
    public void plusAssign(GF other) {
        val = add(this, other).val;
    }
    public void minusAssign(GF other) {
        val = subtract(this, other).val;
    }
    public void multiplyAssign(GF other) {
        val = multiply(this, other).val;
    }
    public void divideAssign(GF other) {
        val = divide(this, other).val;
    }
    @Override
    public String toString() {
        return "p   = " + p + "\nval = " + val;
    }
}
