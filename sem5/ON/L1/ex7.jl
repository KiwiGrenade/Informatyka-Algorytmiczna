# Jakub Jaśków
function f(x)
    return Float64(Float64(sin(x)) + Float64(cos(3.0 * x)))
end

println("Zadanie 7\n")
for n = 0 : 54
    h = Float64(2.0 ^ ((-1.0 * n)))
    x_0 = Float64(1.0)
    fDev = Float64(Float64(f(Float64(x_0 + h)) - f(x_0)) / h)
    println("f`(", x_0, ") = ", fDev, ", h = ", h)
end
# TODO: Calculate abs(trueDev(f) - fDev)
