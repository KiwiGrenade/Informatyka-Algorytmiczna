def check_p(L, R):
    if L.get_p() != R.get_p():
        raise ValueError("[GF]ERROR: not matching p!")


class GF:
    def __init__(self, _p, _val):
        self.__p = 1
        self.__val = 0
        if _p == 0:
            raise ValueError("[GF]ERROR: __p must be > 0")
        self.__p = _p
        self.set_val(_val)

    def get_p(self):
        return self.__p

    def set_p(self, _p):
        self.__p = _p
        self.set_val(self.__val)

    def get_val(self):
        return self.__val

    def set_val(self, _val):
        if _val < 0:
            self.__val = (self.__p + _val) % self.__p
        else:
            self.__val = _val

    def assign(self, R):
        self.__p = R.__p
        self.__val = R.__val

    def __eq__(self, R):
        check_p(self, R)
        return self.__val == R.__val

    def __ne__(self, R):
        return not self == R

    def __lt__(self, R):
        check_p(self, R)
        return self.__val < R.__val

    def __gt__(self, R):
        return R < self

    def __le__(self, R):
        return not self > R

    def __ge__(self, R):
        return not self < R

    def __pos__(self):
        return self

    def __neg__(self):
        return GF(self.__p, self.__p - self.__val)

    def __add__(self, R):
        check_p(self, R)
        _val = (self.__val + R.__val) % self.__p
        return GF(R.__p, _val)

    def __sub__(self, R):
        check_p(self, R)
        return (-R) + self

    def __mul__(self, R):
        check_p(self, R)
        _val = (self.__val * R.__val) % self.__p
        return GF(self.__p, _val)

    def __truediv__(self, R):
        check_p(self, R)
        RValReverse = pow(R.__val, -1, R.__p)
        _val = (self.__val * RValReverse) % self.__p
        return GF(self.__p, _val)

    def __iadd__(self, other):
        self = self + other
        return self

    def __isub__(self, other):
        self = self - other
        return self

    def __imul__(self, other):
        self = self * other
        return self

    def __idiv__(self, other):
        self = self / other
        return self

    def __str__(self):
        return f"__p   = {self.__p}\n__val = {self.__val}"
