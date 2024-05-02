package org.example;

import static org.junit.jupiter.api.Assertions.*;
class DHSetupTest {
//
//    @org.junit.jupiter.api.BeforeEach
//    void setUp() {
//    }

    @org.junit.jupiter.api.Test
    void power() {
        int p = 1234567891;
        int a = 1166403871;
        int b = 581869302;
        DHSetup DH = new DHSetup(p);
        assertEquals(DH.power(new GF(p, a), b).getVal(), 724254047);
    }
}