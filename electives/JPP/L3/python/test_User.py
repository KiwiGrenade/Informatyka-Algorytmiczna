import unittest
from User import User
from DHSetup import DHSetup
from GF import GF

class TestUser(unittest.TestCase):
    def test(self):
        p = 1234567891
        m = 20
        message = GF(p, m)
        DH = DHSetup(p)
        user1 = User(DH)
        user2 = User(DH)

        self.assertNotEqual(user1.get_public_key(), user2.get_public_key())

        user1.set_key(user2.get_public_key())
        user2.set_key(user1.get_public_key())

        encryptedMessage = user1.encrypt(message)
        decryptedMessage = user2.decrypt(encryptedMessage)

        self.assertEqual(decryptedMessage.get_val(), message.get_val())

if __name__ == '__main__':
    unittest.main()
