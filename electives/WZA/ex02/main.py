import sys

from lib import *

def test_add() -> None:
    p1 = Polynomial([1, 2, 2])
    p2 = Polynomial([2, 1])
    p3 = p1 + p2
    assert p3.coeffs == [3, 3, 2]

def test_sub() -> None:
    p1 = Polynomial([3, 1, 1])
    p2 = Polynomial([2, 2, 1])
    p3 = p1 - p2
    assert p3.coeffs == [1, -1]

def test_mul() -> None:
    p1 = Polynomial([1, 2, 1])
    p2 = Polynomial([1, 1])
    p3 = p1 * p2
    assert p3.coeffs == [1, 3, 3, 1]

def test_div() -> None:
    p1 = Polynomial([5, 4, -3, 2])
    p2 = Polynomial([2, 1])
    q, r = p1 / p2
    assert q.coeffs == [18, -7, 2]
    assert r.coeffs == [-31]

def test_gcd() -> None:
    p1 = Polynomial([1, 0, 1])
    p2 = Polynomial([1, 2, 1])
    p3 = gcd(p2, p1)
    assert p3.coeffs == [1]

    p1 = Polynomial([6, 4])
    p2 = Polynomial([3, 2])
    p3 = gcd(p1, p2)
    assert p3.coeffs == [3, 2]

def test_lcm() -> None:
    p1 = Polynomial([1, 0, 1])
    p2 = Polynomial([1, 2, 1])
    p3 = lcm(p2, p1)
    assert p3.coeffs == [1, 2, 2, 2, 1]

def test_gcd_ext() -> None:
    p1 = Polynomial([1, 0, 1])
    p2 = Polynomial([1, 2, 1])
    p3, A, B = gcd_ext(p2, p1)
    res = A * p2 + B * p1
    assert res.coeffs == p3.coeffs

def main() -> int:
    test_add()
    test_sub()
    test_mul()
    test_div()
    test_gcd()
    test_lcm()
    test_gcd_ext() 
    return 0

if __name__ == '__main__':
    sys.exit(main())

