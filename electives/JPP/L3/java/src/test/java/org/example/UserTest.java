package org.example;

import static org.junit.jupiter.api.Assertions.*;

class UserTest {

    @org.junit.jupiter.api.Test
    void elo() {
        long p = 1234567891;
        long m = 20;
        GF message = new GF(p, m);
        DHSetup DH = new DHSetup(p);
        User user1 = new User(DH);
        User user2 = new User(DH);

        assertNotEquals(user1.getPublicKey().getVal(), user2.getPublicKey().getVal());

        user1.setKey(user2.getPublicKey());
        user2.setKey(user1.getPublicKey());

        GF encryptedMessage = user1.encrypt(message);
        GF decryptedMessage = user2.decrypt(encryptedMessage);

        assertEquals(decryptedMessage.getVal(), m);
    }
}