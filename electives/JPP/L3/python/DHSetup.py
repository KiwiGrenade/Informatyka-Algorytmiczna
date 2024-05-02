from GF import GF
from random import randint

class DHSetup:

    def __is_generator(self, a, _p): 
        for q in self.__prime_factors:
            if a * (_p-1)/q == 1:
                return False
        return True
    
    def __trial_division(self, n): 
        f = 2
        while n % 2 == 0 :
            self.__prime_factors.append(f)
            n = int(n / 2)
        f = 3
        while n % 3 == 0:
            self.__prime_factors.append(f)
            n = int(n / 3)
        f = 5
        ac = 9
        temp = 16
        while True:
            ac += temp
            if ac > n:
                break
            if n % f == 0:
                self.__prime_factors.append(f)
                n = int(n / f)
                ac -= temp;
            else:
                f += 2
                temp += 8
        if n != 1:
            self.__prime_factors.append(f)

    def __init__(self, _p): 
        self.__prime_factors = []
        self.__trial_division(_p - 1)
        
        tmp = randint(1, _p-1)
        while(self.__is_generator(tmp, _p-1) == False):
            tmp = randint(1, _p-1)

        self.g = GF(_p, tmp)


    def get_generator(self):
        return self.g

    def power(self, a, b):
        res = GF(a.get_p(), 1)
        while b > 0:
            if b % 2 == 1 :
                res *= a
            b = int(b/2)
            a *= a
        return res
