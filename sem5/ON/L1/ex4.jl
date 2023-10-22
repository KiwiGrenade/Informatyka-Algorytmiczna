# Jakub Jaśków
function ex4ab()
    x = Float64(1.0)
    while nextfloat(x) * Float64(1.0 / nextfloat(x)) == 1.0
        x = nextfloat(x)
    end
    println("Subpoint a) and b)")
    println("Smallest x = $x")
end
println("Zadanie 4\n")
ex4ab()