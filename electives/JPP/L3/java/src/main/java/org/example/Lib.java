package org.example;

public class Lib {
    public static long IFactor(int n) {
        long r = 1;
        for(int i = 2; i <= n; i++) {
            r *= i;
        }
        return r;
    }

    public static long RFactor(int n) {
        if(n < 2) {
            return 1;
        } else {
            return n * RFactor(n-1);
        }
    }

    public static long IGCD(long a, long b) {
        long t;
        while (b != 0) {
            t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    public static long RGCD(long a, long b) {
        if (b == 0) {
            return a;
        } else {
            return RGCD(b, a % b);
        }
    }

    public static long[] ERGCD(long a, long b) {
        long[] result = new long[3];
        if (b == 0) {
            result[0] = a;
            result[1] = 1;
            result[2] = 0;
        } else {
            long[] temp = ERGCD(b, a % b);
            result[0] = temp[0];
            result[1] = temp[2];
            result[2] = temp[1] - (a / b) * temp[2];
        }
        return result;
    }

    public static long[] EIGCD(long a, long b) {
        long x0 = 1, y0 = 0, x1 = 0, y1 = 1;
        while (b != 0) {
            long quotient = a / b;
            long remainder = a % b;
            a = b;
            b = remainder;

            long temp = x1;
            x1 = x0 - quotient * x1;
            x0 = temp;

            temp = y1;
            y1 = y0 - quotient * y1;
            y0 = temp;
        }
        return new long[]{a, x0, y0};
    }

    public static long[] RLDES(long a, long b, long c) {
        if (a == 0 && b == 0) {
            if (c == 0) {
                System.out.println("Infinite Solutions Exist");
            } else {
                System.out.println("No Solution Exists");
            }
            return new long[]{0, 0};
        }
        long[] gcd = ERGCD(a, b);
        if (c % gcd[0] != 0) {
            System.out.println("No Solution Exists");
            return new long[]{0, 0};
        }
        return new long[]{gcd[1], gcd[2]};
    }

    public static long[] ILDES(long a, long b, long c) {
        if (a == 0 && b == 0) {
            if (c == 0) {
                System.out.println("Infinite Solutions Exist");
            } else {
                System.out.println("No Solution Exists");
            }
            return new long[]{0, 0};
        }
        long[] gcd = EIGCD(a, b);
        if (c % gcd[0] != 0) {
            System.out.println("No Solution Exists");
            return new long[]{0, 0};
        }
        return new long[]{gcd[1], gcd[2]};
    }
}