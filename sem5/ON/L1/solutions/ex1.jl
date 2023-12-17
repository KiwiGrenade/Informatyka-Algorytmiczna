# Jakub Jaśków

function getEps(type)
    machinEps = type(1.0)
    while(type(1.0 + 0.5 * machinEps) > type(1.0))
        machinEps = type(machinEps * 0.5)
    end
    println("$type iterative epsilon = $machinEps")
end

function getEta(type)
    eta = type(1.0)
    while(type(eta * 0.5) > 0.0)
        eta = type(eta * 0.5)
    end
    println("Iterative eta $type = $eta")
end

function getMax(type)
    max = prevfloat(type(1.0))
    while isinf(type(max * 2.0)) == false
        max *= type(2.0)
    end
    println("Max iterative $type =  $max")
end

floatTypes = [Float16, Float32, Float64]

println("Zadanie 1.1\n")
for type in floatTypes
    getEps(type)
    println("eps($type) = ", eps(type), '\n')
end

println("\nZadanie 1.2\n")
for type in floatTypes
    getEta(type)
    println("Eta nextfloat($type) = ", nextfloat(type(0.0)), '\n')
end

println("\nZadanie 1.3\n")
for type in floatTypes
    getMax(type)
    println("floatmax($type) = ", floatmax(type), '\n')
end