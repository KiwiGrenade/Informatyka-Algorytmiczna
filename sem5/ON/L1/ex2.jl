# Jakub Jaśków
println("Zadanie 2")
println("\nFloat16(1 - 3(4/3-1)) = ", Float16(1.0 - 3.0*Float16(Float16(4.0 / 3.0) - 1.0)))
println("macheps(Float16) = ", eps(Float16))
println("\nFloat32(1 - 3(4/3-1)) = ", Float32(1.0 - 3.0*Float32(Float32(4.0 / 3.0) - 1.0)))
println("macheps(Float32) = ", eps(Float32))
println("\nFloat64(1 - 3(4/3-1)) = ", Float64(1.0 - 3.0*Float64(Float64(4.0 / 3.0) - 1.0)))
println("macheps(Float64) = ", eps(Float64))