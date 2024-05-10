package org.example;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class GF implements GFI {
    private long p;
    private long val;

    private static void checkP(@NotNull GF L, @NotNull GF R) {
        if(L.p != R.p)
            throw new IllegalArgumentException("[GF]ERROR: not matching p!");
    }
    private static long inverse(long _p, long _val){
        return _p + (_val % _p);
    }

    public GF() {
        p = 0;
        setVal(0);
    }
    public GF(long _p, long _val) {
        if(_p == 0) {
            throw new IllegalArgumentException("[GF]ERROR: p must be > 0");
        }
        p = _p;
        setVal(_val);
    }

    @Override
    public GF instantiate(long _p, long _val) {
        return new GF();
    }
    @Override
    public long getP() { return p; }
    @Override
    public void setP(long _p) { p = _p; setVal(val); }
    @Override
    public long getVal() {
        return val;
    }
    @Override
    public void setVal(long _val) {
        if(_val < 0 ) {
            val = inverse(p, _val);
        }
        else {
            val = _val % p;
        }
    }


    // compare
    @Override
    public boolean equals(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        return L.val == R.val;
    }
    @Override
    public boolean notEquals(@NotNull GF L, @NotNull GF R) {
        return !equals(L, R);
    }
    @Override
    public boolean lessThan(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        return L.val < R.val;
    }
    @Override
    public boolean greaterThan(@NotNull GF L, @NotNull GF R) {
        return lessThan(R, L);
    }
    @Override
    public boolean lessThanOrEqual(@NotNull GF L, @NotNull GF R) {
        return !greaterThan(L, R);
    }
    @Override
    public boolean greaterThanOrEqual(@NotNull GF L, @NotNull GF R) {
        return !lessThan(L, R);
    }

    // arithmetic
    @Override
    public GF plus() {
        return this;
    }
    @Override
    public GF minus() {
        return new GF(this.p, this.p - this.val);
    }
    @Override
    @Contract("_, _ -> new")
    public GF add(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        long _val = (L.val + R.val) % L.p;
        return new GF(R.p, _val);
    }
    @Override
    @Contract("_, _ -> new")
    public GF subtract(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        R = R.minus();
        return add(R, L);
    }
    @Override
    @Contract("_, _ -> new")
    public GF multiply(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        return new GF(L.p, (L.val * R.val) % L.p);
    }
    @Override
    @Contract("_, _ -> new")
    public GF divide(@NotNull GF L, @NotNull GF R) {
        checkP(L, R);
        long RValReverse = Lib.ILDES(R.val, R.p, Lib.IGCD(R.val, R.p))[0];
        GF result = new GF(R.p, RValReverse);
        return multiply(L, result);
    }

    // assign
    @Override
    public void assign(@NotNull GF other) {
        setP(other.p);
        setVal(other.val);
    }
    @Override
    public void plusAssign(@NotNull GF other) {
        val = add(this, other).val;
    }
    @Override
    public void minusAssign(@NotNull GF other) {
        val = subtract(this, other).val;
    }
    @Override
    public void multiplyAssign(@NotNull GF other) {
        val = multiply(this, other).val;
    }
    @Override
    public void divideAssign(@NotNull GF other) {
        val = divide(this, other).val;
    }

    @Override
    public String toString() {
        return "p   = " + p + "\nval = " + val;
    }
}
