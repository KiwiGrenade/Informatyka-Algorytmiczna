# Jakub Jaśków
function f(x)
    return sin(x) + cos(3.0 * x)
end

function fDev(x, h)
    return Float64(Float64(f(Float64(x + h)) - f(x)) / h)
end

function df(x)
    return Float64(cos(x) - Float64(3.0 * sin(Float64(3.0 * x))))
end

println("Zadanie 7\n")
println(rpad('h', 15), rpad("df", 35), rpad("|fDev - df|", 35),rpad("1+h", 35))
println('-'^85)
for n = 0 : 54
    h = 2.0 ^ -n
    x_0 = Float64(1.0)
    println(rpad("2.0^-$n", 15), rpad(fDev(x_0, h), 35), rpad(abs(Float64(fDev(x_0, h) - df(x_0))), 35),rpad(Float64(1+h), 35))
end
