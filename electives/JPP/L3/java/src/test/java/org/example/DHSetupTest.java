package org.example;

import static org.junit.jupiter.api.Assertions.*;
class DHSetupTest {

    @org.junit.jupiter.api.Test
    void power() {
        long p = 1234567891;
        long a = 1166403871;
        long b = 581869302;
        DHSetup DH = new DHSetup(p);
        GF A = new GF(p, a);
        assertEquals(DH.power(A, b).getVal(), 724254047);
    }
}