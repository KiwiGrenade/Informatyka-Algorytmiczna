from typing import List

import numpy

class polynomial():
    def __init__(self, coeffs: List[float]) -> None:
        self._coeffs = coeffs

    @property
    def coeffs(self) -> List[float]:
        return self._coeffs

    @property
    def deg(self) -> int:
        if not any(self.coeffs):
            return 0
        return len(self.coeffs)

    def __str__(self) -> str:
        return str(self.coeffs)
    
    def __add__(self, other) -> 'polynomial':
        coeffs_n = list(numpy.polynomial.polynomial.polyadd(self.coeffs, other.coeffs))
        return polynomial(coeffs_n)

    def __sub__(self, other) -> 'polynomial':
        coeffs_n = list(numpy.polynomial.polynomial.polysub(self.coeffs, other.coeffs))
        return polynomial(coeffs_n)

    def __mul__(self, other) -> 'polynomial':
        prod = [0] * (self.deg + other.deg - 1)
        for i in range(self.deg):
            for j in range(other.deg):
                prod[i + j] += (self.coeffs[i] * other.coeffs[j])

        return polynomial(prod)

    def __truediv__(self, other) -> tuple['polynomial', 'polynomial']:
        q, r =  numpy.polynomial.polynomial.polydiv(self.coeffs, other.coeffs)
        return polynomial(list(q)), polynomial(list(r))


def gcd(x: polynomial, y: polynomial) -> polynomial:
    if x.deg < y.deg:
        return gcd(y, x)
    if y.deg == 0:
        return x
    _, r = x / y
    return gcd(y, r)

def gcd_ext(x: polynomial, y: polynomial) -> tuple[polynomial, polynomial, polynomial]:
    if x.deg < y.deg:
        return gcd_ext(y, x)
    if y.deg == 0:
        return x, polynomial([1]), polynomial([0])

    q, r = x / y
    d, X, Y = gcd_ext(y, r)
    return d, Y, X - Y * q

def lcm(x: polynomial, y: polynomial) -> polynomial:
    gcd_ = gcd(x, y)
    mul = x * y
    return (mul / gcd_)[0]
