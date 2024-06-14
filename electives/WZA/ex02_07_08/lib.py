from typing import List, Tuple

import numpy

class Polynomial:
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
    
    def __add__(self, other) -> 'Polynomial':
        coeffs_n = list(numpy.polynomial.polynomial.polyadd(self.coeffs, other.coeffs))
        return Polynomial(coeffs_n)

    def __sub__(self, other) -> 'Polynomial':
        coeffs_n = list(numpy.polynomial.polynomial.polysub(self.coeffs, other.coeffs))
        return Polynomial(coeffs_n)

    def __mul__(self, other) -> 'Polynomial':
        prod = [0] * (self.deg + other.deg - 1)
        for i in range(self.deg):
            for j in range(other.deg):
                prod[i + j] += (self.coeffs[i] * other.coeffs[j])

        return Polynomial(prod)

    def __truediv__(self, other) -> Tuple['Polynomial', 'Polynomial']:
        q, r =  numpy.polynomial.polynomial.polydiv(self.coeffs, other.coeffs)
        return Polynomial(list(q)), Polynomial(list(r))


def gcd(x: Polynomial, y: Polynomial) -> Polynomial:
    if x.deg < y.deg:
        return gcd(y, x)
    if y.deg == 0:
        return x
    _, r = x / y
    return gcd(y, r)

def gcd_ext(x: Polynomial, y: Polynomial) -> Tuple[Polynomial, Polynomial, Polynomial]:
    if x.deg < y.deg:
        return gcd_ext(y, x)
    if y.deg == 0:
        return x, Polynomial([1]), Polynomial([0])

    q, r = x / y
    d, X, Y = gcd_ext(y, r)
    return d, Y, X - Y * q

def lcm(x: Polynomial, y: Polynomial) -> Polynomial:
    gcd_ = gcd(x, y)
    mul = x * y
    return (mul / gcd_)[0]
