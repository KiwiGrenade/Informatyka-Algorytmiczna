# Jakub Jaśków
function f(x)
    return Float64(sqrt(Float64(Float64(x^2.0)+1.0))-1.0)
end

function g(x)
    x2 = Float64(x^2.0)
    return Float64(x2 / Float64(sqrt(Float64(x2 + 1.0))+1.0))
end

println("Zadanie 6\n")
println(rpad('x', 15), rpad("f(x)", 35), rpad("g(x)", 35))
println('-' ^ 85)
for c = 1:20
    x = 8^((-1.0) * c)
    println(rpad("8^-$c", 15), rpad(f(x), 35), rpad(g(x), 35))
end