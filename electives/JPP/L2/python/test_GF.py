import unittest
import random
from GF import GF


class TestGF(unittest.TestCase):
    def setUp(self):
        self.p: int = 1234577
        self.val1: int = random.randint(0, self.p - 1)
        self.val2: int = random.randint(0, self.p - 1)
        self.L = GF(self.p, self.val1)
        self.R = GF(self.p, self.val2)
        self.C = GF(self.p, 0)

    def test_assignment(self):
        self.C.assign(self.L)
        self.assertEqual(self.L.get_p(), self.C.get_p())
        self.assertEqual(self.L.get_val(), self.C.get_val())

    def test_addition(self):
        self.C = GF(self.p, (self.val1 + self.val2) % self.p)
        self.assertEqual(self.L + self.R, self.C)

    def test_subtraction(self):
        exp_res: int = (self.L.get_val() + (self.R.get_p() - self.R.get_val())) % self.R.get_p()
        C = self.L - self.R
        self.assertEqual(C.get_val(), exp_res)

    def test_multiplication(self):
        exp_res: int = (self.L.get_val() * self.R.get_val()) % self.R.get_p()
        C = self.L * self.R
        self.assertEqual(C.get_val(), exp_res)

    def test_division(self):
        exp_res: int = (self.L.get_val() * pow(self.R.get_val(), -1, self.R.get_p())) % self.R.get_p()
        C = self.L / self.R
        self.assertEqual(C.get_val(), exp_res)

    def test_equality(self):
        self.assertFalse(self.L == GF(self.p, self.val1 + 1))
        self.assertTrue(self.L == self.L)

    def test_less_than(self):
        self.assertTrue(self.L < GF(self.p, self.val1 + 1))
        self.assertFalse(self.L < self.L)

    def test_greater_than(self):
        self.assertTrue(self.L > GF(self.p, self.val1 - 1))
        self.assertFalse(self.L > self.L)

    def test_less_than_or_equal_to(self):
        self.assertTrue(self.R <= GF(self.p, self.val2 + 1))
        self.assertTrue(self.R <= self.R)
        self.assertFalse(self.R <= GF(self.p, self.val2 - 1))

    def test_greater_than_or_equal_to(self):
        self.assertTrue(self.R >= GF(self.p, self.val2 - 1))
        self.assertTrue(self.R >= self.R)
        self.assertFalse(self.R >= GF(self.p, self.val2 + 1))

    def test_negation(self):
        self.assertEqual(-self.L, GF(self.p, self.p - self.val1))

    def test_positivity(self):
        self.assertEqual(+self.L, self.L)

    def test_str(self):
        self.assertEqual(str(self.L), f"__p   = {self.L.get_p()}\n__val = {self.L.get_val()}")

    def test_iadd(self):
        self.C.assign(self.L + self.R)
        self.L += self.R
        self.assertTrue(self.L == self.C)

    def test_isub(self):
        self.C.assign(self.L - self.R)
        self.L -= self.R
        self.assertTrue(self.L == self.C)

    def test_imul(self):
        self.C.assign(self.L * self.R)
        self.L *= self.R
        self.assertTrue(self.L == self.C)

    def test_idiv(self):
        self.C.assign(self.L / self.R)
        self.L /= self.R
        self.assertTrue(self.L == self.C)


if __name__ == '__main__':
    unittest.main()