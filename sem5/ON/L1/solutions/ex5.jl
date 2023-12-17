# Jakub Jaśków
# A)
function forwards(x, y, type, n)
    S = type(0.0)
    for i = 1:n
        S = type(S + type(x[i] * y[i]))
    end
    println("forward$type S = ", S)
end

# B) 
function backwards(x, y, type, n)
    S = type(0.0)
    for i = n:-1:1
        S = type(S + type(x[i] * y[i]))
    end
    println("backwards$type S = ", S)
end

# C -> negate => maxToMax, -> !negate => minToMin
function maxToMax(x, y, type, negate)
    z = x .* y

    posVal = filter(x -> x > 0, z)
    negVal = filter(x -> x < 0, z)
    posVal = sort(posVal, rev = !negate) # max -> min
    negVal = sort(negVal, rev = negate) # min -> max
    posSum = type(0)
    negSum = type(0)

    # sum(posVal)

    for i in eachindex(posVal)
        posSum = type(posSum + posVal[i])
    end
    for i in eachindex(negVal)
        negSum = type(negSum + negVal[i])
    end

    sum = type(posSum + negSum)
    println("maxToMax$type sum = ", sum)
end

floatTypes = [Float32, Float64]
Vx = [2.718281828,−(3.141592654),1.414213562,0.5772156649,0.3010299957]
Vy = [1486.2497,878366.9879,−(22.37492),4773714.647,0.000185049]
println("Zadanie 5")
for type in floatTypes
    x = Array{type, 1}(Vx)
    y = Array{type, 1}(Vy)
    println("\nreal = -1.00657107000000e-11")
    forwards(x, y, type, 5)
    backwards(x, y, type, 5)
    maxToMax(x, y, type, false)
    maxToMax(x, y, type, true)
end