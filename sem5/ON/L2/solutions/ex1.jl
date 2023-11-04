# Jakub Jaśków 268416
# A)
function forwards(x, y, type, n)
    S = type(0.0)
    for i = 1:n
        S = type(S + type(x[i] * y[i]))
    end
    return type(S)
end

# B) 
function backwards(x, y, type, n)
    S = type(0.0)
    for i = n:-1:1
        S = type(S + type(x[i] * y[i]))
    end
    return type(S)
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
    return type(sum)
end

floatTypes = [Float32, Float64]
oldX = [2.718281828,−(3.141592654),1.414213562,0.5772156649,0.3010299957]
newX = [2.718281828,−(3.141592654),1.414213562,0.577215664,0.301029995]
Y = [1486.2497,878366.9879,−(22.37492),4773714.647,0.000185049]



println("Zadanie 1")
for type in floatTypes
    oldX_ = Array{type, 1}(oldX)
    newX_ = Array{type, 1}(newX)
    y = Array{type, 1}(Y)
    oldVal = []
    newVal = []

    push!(oldVal, forwards(oldX_, y, type, 5))
    push!(oldVal, backwards(oldX_, y, type, 5))
    push!(oldVal, maxToMax(oldX_, y, type, false))
    push!(oldVal, maxToMax(oldX_, y, type, true))

    push!(newVal, forwards(newX_, y, type, 5))
    push!(newVal, backwards(newX_, y, type, 5))
    push!(newVal, maxToMax(newX_, y, type, false))
    push!(newVal, maxToMax(newX_, y, type, true))

    println(type)
    dist1 = 20
    dist2 = 25
    println('|', rpad("function", dist1),       '|', rpad("new", dist2),     '|', rpad("old", dist2),     '|')
    println('|', rpad("forwards()", dist1),     '|', rpad(newVal[1], dist2), '|', rpad(oldVal[1], dist2), '|')
    println('|', rpad("backwards()", dist1),    '|', rpad(newVal[2], dist2), '|', rpad(oldVal[2], dist2), '|')
    println('|', rpad("maxToMax()", dist1),     '|', rpad(newVal[3], dist2), '|', rpad(oldVal[3], dist2), '|')
    println('|', rpad("revmaxToMax()", dist1),  '|', rpad(newVal[4], dist2), '|', rpad(oldVal[4], dist2), '|')
end
println("\nreal = -1.00657dist17000000e-11")
