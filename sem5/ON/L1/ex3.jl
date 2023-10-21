# Jakub Jaśków
# TODO: complete this exercise
function ex3(a, b)
    eta = Float64(2^(-52))
    y = Float64(a)
    k = 1
    isEta
    while(y < 2)
        y = nextfloat(y)
        x = Float64(1.0 + Float64(k * eta))
        if(y != x)
            break;
            k += 1
        end
    end
    
println("Zadanie 3\n")
#ex3()
println()
