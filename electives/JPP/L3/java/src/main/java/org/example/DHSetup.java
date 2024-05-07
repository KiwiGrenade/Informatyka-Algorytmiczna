package org.example;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DHSetup {
    private final GF g;
    private static final Random rng = new Random();
    private final List<Long> primeFactors = new ArrayList<>();

    private boolean isGenerator(long a, long _p) {
        for(long q : primeFactors) {
            if(a * (_p-1)/q == 1)
                return false;
        }
        return true;
    }

    private void TrialDivision(long n) {
        long f;
        f = 2;
        while (n % 2 == 0) { primeFactors.add(f); n /= 2; }
        f = 3;
        while (n % 3 == 0) { primeFactors.add(f); n /= 3; }
        f = 5;
        long ac = 9, temp = 16;
        do {
            ac += temp; // Assume addition does not cause overflow with U type
            if (ac > n) break;
            if (n % f == 0) {
                primeFactors.add(f);
                n /= f;
                ac -= temp;
            }
            else {
                f += 2;
                temp += 8;
            }
        } while (true);
        if (n != 1) primeFactors.add(n);
    }

    public DHSetup(long _p) {
        TrialDivision(_p - 1);

        long tmp;
        do {tmp = rng.nextLong(_p) + 1;}
        while(isGenerator(tmp, _p-1) == false);
        g = new GF(_p, tmp);
    }

    public GF getGenerator() {
        return g;
    }

    public GF power(GF a, long b) {
        GF res = new GF(a.getP(), 1);
        GF tmp = new GF(a.getP(), a.getVal());
        while(b > 0) {
            if(b % 2 == 1) {
                res.multiplyAssign(tmp);
            }
            b /= 2; // b /= 2
            tmp.multiplyAssign(tmp);
        }
        return res;
    }
}