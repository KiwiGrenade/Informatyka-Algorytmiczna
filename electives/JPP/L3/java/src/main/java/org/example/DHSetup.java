package org.example;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class DHSetup {
    private GF g;
    private Class<GF> gClass;
    private static final Random rng = new Random();
    private List<Integer> primeFactors = new ArrayList<>();

    private boolean isGenerator(int a, int _p) {
        for(int q : primeFactors) {
            if(a * (_p-1)/q == 1)
                return false;
        }
        return true;
    }

    private void GFrialDivision(int n) {
        int f;
        f = 2;
        while (n % 2 == 0) { primeFactors.add(f); n /= 2; }
        f = 3;
        while (n % 3 == 0) { primeFactors.add(f); n /= 3; }
        f = 5;
        int ac = 9, temp = 16;
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

    public DHSetup(int _p) {
        GFrialDivision(_p - 1);

        int tmp;
        do {tmp = rng.nextInt(_p) + 1;}
        while(isGenerator(tmp, _p-1) == false);
        g = new GF(_p, tmp);
    }

    public GF getGenerator() {
        return g;
    }

    public GF power(GF a, long b) {
        GF res = new GF(a.getP(), b);
        while(b > 0) {
            if((b & 1) == 1) {
                res.multiplyAssign(a);
            }
            b /= 2; // b /= 2
            res.multiplyAssign(a);
        }
        return res;
    }
}