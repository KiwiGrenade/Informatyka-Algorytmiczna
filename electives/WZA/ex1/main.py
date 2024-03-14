def gcd_gaussian(a, b):
    # Extended Euclidean algorithm for complex numbers
    while b.real != 0 or b.imag != 0:
        temp_real = b.real
        temp_imag = b.imag
        # Perform division with complex conjugate of b
        quotient = (a * temp_real + a * temp_imag * 1j) / (temp_real ** 2 + temp_imag ** 2)
        # Round the result to avoid precision errors
        quotient = round(quotient.real) + round(quotient.imag) * 1j
        a, b = b, a - quotient * b
    return a

# Test the function
a = 12 + 8j
b = 18 + 6j
result = gcd_gaussian(a, b)
print("GCD of", a, "and", b, "is", result)
