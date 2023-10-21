# Jakub Jaśków
floatTypes = [Float16, Float32, Float64]
println("Zadanie 2")
for type in floatTypes
    println('\n', type, "(3(4/3-1) - 1) = ", type(3.0*type(type(4.0 / 3.0) - 1.0) - 1))
    println("macheps(", type, ") = ", eps(type))
end