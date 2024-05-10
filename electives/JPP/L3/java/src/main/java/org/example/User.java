package org.example;

import java.util.Random;

public class User {
    private DHSetup dh = null;
    private long secret;
    private static final Random rng = new Random();
    private GF key = null;

    public User(DHSetup _dh) {
        dh = _dh;
        secret = rng.nextLong(1, 404967290);
    }

    public GF getPublicKey(){
        return dh.power(dh.getGenerator(), secret);
    }

    public void setKey(GF a) {
        key = dh.power(a, secret);
    }

    public GF encrypt(GF m) {
        return m.multiply(m, key);
    }

    public GF decrypt(GF m) {
        return m.divide(m, key);
    }
}
