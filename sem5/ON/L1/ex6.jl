# Jakub Jaśków
function f(x)
    result = Float64(sqrt(Float64(Float64(x^2.0)+1.0))-1.0)
    println("f(", x, ") = ", result)
end

function g(x)
    x2 = Float64(x^2.0)
    result = Float64(x2 / Float64(sqrt(Float64(x2 + 1.0))+1.0))
    println("g(", x, ") = ", result)
end

println("Zadanie 6\n")
for c = 1:10
    f(8^((-1.0) * c))
end
println()
for c = 1:10
    g(8^((-1.0) * c))
end