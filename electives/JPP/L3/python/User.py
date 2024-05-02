from DHSetup import DHSetup
from random import randint

class User:
    def __init__(self, _dh):
        self.DH = _dh
        self.secret = randint(1, 4294967295)
    
    def get_public_key(self):
        return self.DH.power(self.DH.get_generator(), self.secret)
    
    def set_key(self, a):
        self.key = self.DH.power(a, self.secret)

    def encrypt(self, m):
        return m * self.key
    
    def decrypt(self, c):
        return c / self.key

