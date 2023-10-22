# Jakub Jaśków

function presenter(start, finish, del)
    println(start) 
    for k = 1:5
        x = Float64(start + k*del)
        println(bitstring(x))
    end
    println()
end
println("Zadanie 3\n")

presenter(1.0,2.0,2^(-52))
presenter(0.5,1.0,2^(-53))
presenter(2.0,4.0,2^(-51))