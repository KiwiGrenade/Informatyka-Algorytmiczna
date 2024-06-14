import random
import sys

from itertools import combinations

def KSA(key):
    key_length = len(key)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % key_length]) % 256
        S[i], S[j] = S[j], S[i]
    return S

def PRGA(S):
    i = 0
    j = 0
    while True:
        i = (i + 1) % 256
        j = (j + S[i]) % 256
        S[i], S[j] = S[j], S[i]
        K = S[(S[i] + S[j]) % 256]
        yield K

def RC4(key):
    S = KSA(key)
    return PRGA(S)

def encrypt(plaintext, key):
    key = [ord(c) for c in key]
    keystream = RC4(key)
    ciphertext = []
    for char in plaintext:
        val = ("%02X" % (ord(char) ^ next(keystream)))
        ciphertext.append(val)
    return ''.join(ciphertext)

def decrypt(ciphertext, key):
    key = [ord(c) for c in key]
    keystream = RC4(key)
    ciphertext = bytes.fromhex(ciphertext)
    plaintext = []
    for char in ciphertext:
        val = chr(char ^ next(keystream))
        plaintext.append(val)
    return ''.join(plaintext)

def uses_same_key(ciphertext0: bytes, ciphertext1: bytes) -> bool:
    for i in range(min(len(ciphertext0), len(ciphertext1))):
        if (ciphertext0[i] ^ ciphertext1[i]) >= 0x80:
            return False
    return True

import random
from itertools import combinations

def gen_bank_numbers(q):
    bank_numbers = []
    numery_rozliczeniowe = [
        [1, 0, 1, 0, 0, 0, 0, 0], # NBP
        [1, 1, 6, 0, 0, 0, 0, 6], # Millenium
        [1, 0, 5, 0, 0, 0, 0, 2], # ING
        [2, 1, 2, 0, 0, 0, 0, 1], # Santander
        [1, 0, 2, 0, 0, 0, 0, 3], # PKO BP
    ]
    random.seed(2137)
    for nr in numery_rozliczeniowe:
        for _ in range(q):
            bank_number = ""
            client_number = [random.randint(0, 9) for _ in range(16)]
            tmp = 212500
            for i in range(8):
                tmp += nr[i] * 10 ** (7 - i + 21)
            for i in range(16):
                tmp += client_number[i] * 10 ** (15 - i + 5)
            tmp = tmp % 97
            tmp = 98 - tmp
            bank_number += f"{tmp:02}"
            for i in range(8):
                bank_number += str(nr[i])
            for i in range(16):
                bank_number += str(client_number[i])
            bank_numbers.append(bank_number)
    return bank_numbers

def calculte_nr_control_number(nr):
    weights = [3, 9, 7, 1, 3, 9, 7]
    sum = 0
    for i in range(7):
        sum += nr[i] * weights[i]
    return (10 - (sum % 10)) % 10
  
def detect_account_numbers(possible_xors):
    detected_numbers = []

    for xor_result in possible_xors:
        possible_digits = []

        for byte in xor_result:
            # Zakładamy, że wynik XOR powinien być w zakresie cyfr 0-9 (ASCII 48-57)
            if 0 <= byte <= 9:
                possible_digits.append(byte)

        if len(possible_digits) == len(xor_result):
            detected_numbers.append(possible_digits)

    return detected_numbers

def ex3():
    bank_numbers = gen_bank_numbers(10)
    key = "Very Good Key"
    cryptograms = []
    possible_xors = []
    for bank_number in bank_numbers:
        cryptogram = encrypt(str(bank_number), key)
        cryptograms.append(bytes.fromhex(cryptogram))

    for c0, c1 in combinations(cryptograms, 2):
        xored = [i0 ^ i1 for i0, i1 in zip(c0, c1)]
        possible_xors.append(xored)

    detected_numbers = detect_account_numbers(possible_xors)

    for digits in detected_numbers:
        print(f"Possible account numbers: {digits}")

def ex12(key, key_prime):
    plaintext = 'Hello, World!'

    # Szyfrowanie przy użyciu klucza key
    ciphertext = encrypt(plaintext, key)
    print(f'Ciphertext with key: {ciphertext}')

    # Deszyfrowanie przy użyciu klucza key
    decrypted_text = decrypt(ciphertext, key)
    print(f'Decrypted text with key: {decrypted_text}')

    # Szyfrowanie przy użyciu klucza key_prime
    ciphertext_prime = encrypt(plaintext, key_prime)
    print(f'Ciphertext with key_prime: {ciphertext_prime}')

    # Deszyfrowanie przy użyciu klucza key_prime
    decrypted_text_prime = decrypt(ciphertext_prime, key_prime)
    print(f'Decrypted text with key_prime: {decrypted_text_prime}')

    if uses_same_key(bytes.fromhex(ciphertext), bytes.fromhex(ciphertext_prime)):
        print("SAME KEY WAS USED!")

    # Sprawdzenie poprawności
    assert plaintext == decrypted_text, "Decryption failed with key!"
    assert plaintext == decrypted_text_prime, "Decryption failed with key_prime!"

def main():
    key = sys.argv[1]
    key_prime = sys.argv[2]

    ex12(key, key_prime)
    ex3() 


if __name__ == '__main__':
    main()