function gcd(a::Int64, b::Int64)
    while b != 0
        a, b = b, a % b
    end
    return abs(a) # Return absolute value to handle negative inputs
end

function lcm(a::Int64, b::Int64)
    return abs(a*b) / gcd(a, b)
end

# Podpunkt A) - GCD dla liczb Euklidesowych
function gcd_complex(a::Complex, b::Complex)
    real_part = gcd(real(a), real(b))
    imag_part = gcd(imag(a), imag(b))
    return complex(real_part, imag_part)
end

# Podpunkt B) - LCM dla liczb Euklidesowych
function lcm_complex(a::Complex, b::Complex)
    real_part = lcm(real(a), real(b))
    imag_part = lcm(imag(a), imag(b))
    return complex(real_part, imag_part)
end

num1 = 40 + 4im
num2 = 20 + 3im

gcd_result = gcd_complex(num1, num2)
println("Greatest Common Divisor (GCD) of $num1 and $num2 is: ", gcd_result)
lcm_result = lcm_complex(num1, num2)
println("Least Common Multiple (LCM) of $num1 and $num2 is: ", lcm_result)
