import unittest
from DHSetup import DHSetup
from GF import GF

class TestDHSetup(unittest.TestCase):
    def test(self):
        p = 1234567891
        a = 1166403871
        b = 581869302
        DH = DHSetup(p)
        self.assertEqual(DH.power(GF(p, a), b).get_val(), 724254047) 

if __name__ == '__main__':
    unittest.main()
