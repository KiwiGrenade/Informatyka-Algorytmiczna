package org.example;

public class GF {
    private int p;
    private long val;

    public GF(int _p, long _val) {
        if(_p == 0) {
            throw new IllegalArgumentException("[GF]ERROR: p must be > 0");
        }
        this.p = _p;
        this.setVal(_val);
    }

    public int getP() {
        return this.p;
    }

    public void setP(int _p) {
        this.p = _p;
        this.setVal(this.val);
    }

    public long getVal() {
        return this.val;
    }

    public void setVal(long _val) {
        if(_val < 0 ) {
            this.val = (this.p + _val) % this.p;
        }
        else {
            this.val = _val;
        }
    }

    private static void checkP(GF L, GF R) {
        if(L.p != R.p)
            throw new IllegalArgumentException("[GF]ERROR: not matching p!");
    }

    // compare
    public boolean equals(GF R) {
        checkP(this, R);
        return this.val == R.val;
    }

    public boolean notEquals(GF R) {
        return !this.equals(R);
    }

    public boolean lessThan(GF R) {
        checkP(this, R);
        return this.val < R.val;
    }

    public boolean greaterThan(GF R) {
        return R.lessThan(this);
    }

    public boolean lessThanOrEqual(GF R) {
        return !this.greaterThan(R);
    }

    public boolean greaterThanOrEqual(GF R) {
        return !this.lessThan(R);
    }

    // arithmetic
    public GF plus() {
        return this;
    }

    public GF minus() {
        return new GF(this.p, (this.p - this.val) % p);
    }

    public GF subtract(GF R) {
        checkP(this, R);
        return this.minus().add(R);
    }

    public GF add(GF R) {
        checkP(this, R);
        long _val = (this.val + R.val) % this.p;
        return new GF(R.p, _val);
    }

    public GF multiply(GF R) {
        checkP(this, R);
        long _val = (this.val * R.val) % this.p;
        return new GF(this.p, _val);
    }

    public GF divide(GF R) {
        checkP(this, R);
        long RValReverse = Lib.iLDES(R.val, R.p, Lib.iGCD(R.val, R.p))[0];
        long _val = (this.val * RValReverse) % this.p;
        return new GF(this.p, _val);
    }

    // assignment
    // TODO: fix this
    public GF plusEquals(GF other) {
        this.setVal();
        return this;
    }
    // TODO: fix this
    public GF minusEquals(GF other) {
//        this.setVal((this.subtract(other)).getVal());
        return this;
    }

    public GF multiplyEquals(GF other) {
        this.setVal((this.multiply(other)).getVal());
        return this;
    }

    public GF divideEquals(GF other) {
        this.setVal((this.divide(other)).getVal());
        return this;
    }

    @Override
    public String toString() {
        return "p   = " + this.p + "\nval = " + this.val;
    }
}