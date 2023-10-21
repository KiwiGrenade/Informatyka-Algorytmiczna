# Jakub Jaśków
println("Zadanie 4\n")
function ex4ab()
    x = nextfloat(Float64(1.0))
    while(Float64(x * Float64(1.0 / x)) == Float64(1.0))
        x = nextfloat(Float64(x))
    end
    println("Subpoint a) and b)")
    println("Smallest x that \\/\\/: x = ", x)
    println("Float64(x * Float64(1.0 / x)) == ", Float64(x * Float64(1.0/x)))
end
ex4ab()
