# Jakub Jaśków
# A)
function forwardsFloat32(x, y)
    x = convert(Array{Float32, 1}, x)
    y = convert(Array{Float32, 1}, y)
    S = Float32(0.0)
    for i = 1:5
        S = Float32(S + Float32(x[i] * y[i]))
    end
    println("forwardsFloat32: S = ", S)
end

function forwardsFloat64(x, y)
    x = convert(Array{Float64, 1}, x)
    y = convert(Array{Float64, 1}, y)
    S = Float64(0.0)
    for i = 1:5
        S = Float64(S + Float64(x[i] * y[i]))
    end
    println("forwardsFloat64: S = ", S)
end

# B) 
function backwardsFloat32(x, y)
    x = convert(Array{Float32, 1}, x)
    y = convert(Array{Float32, 1}, y)
    S = Float32(0.0)
    for i = 5:1
        S = Float32(S + Float32(x[i] * y[i]))
    end
    println("backwardsFloat32: S = ", S)
end

function backwardsFloat64(x, y)
    x = convert(Array{Float64, 1}, x)
    y = convert(Array{Float64, 1}, y)
    S = Float64(0.0)
    for i = 5:1
        S = Float64(S + Float64(x[i] * y[i]))
    end
    println("backwardsFloat64: S = ", S)
end

# C)
function maxToMaxFloat32(x, y)
    x = convert(Array{Float32, 1}, x)
    y = convert(Array{Float32, 1}, y)
    z = convert(Array{Float32, 1}, vcat(x, y))

    posVal = filter(x -> x > 0 == true, z)
    negVal = filter(x -> x < 0 == true, z)
    
    posVal = sort(posVal, rev = true) # max -> min
    negVal = sort(negVal) # min -> max

    posSum = Float32(0.0)
    negSum = Float32(0.0)

    for i in eachindex(posVal)
        posSum = Float32(posSum + posVal[i])
    end
    for i in eachindex(negVal)
        negSum = Float32(negSum + negVal[i])
    end
    
    sum = Float32(posSum + negSum)

    println("maxToMaxFloat32: sum = ", sum)
end

function maxToMaxFloat64(x, y)
    x = convert(Array{Float64, 1}, x)
    y = convert(Array{Float64, 1}, y)
    z = convert(Array{Float64, 1}, vcat(x, y))

    posVal = filter(x -> x > 0 == true, z)
    negVal = filter(x -> x < 0 == true, z)
    
    posVal = sort(posVal, rev = true) # max -> min
    negVal = sort(negVal) # min -> max

    posSum = Float64(0.0)
    negSum = Float64(0.0)

    for i in eachindex(posVal)
        posSum = Float64(posSum + posVal[i])
    end
    for i in eachindex(negVal)
        negSum = Float64(negSum + negVal[i])
    end
    
    sum = Float64(posSum + negSum)

    println("maxToMaxFloat64: sum = ", sum)
end

# D)
function minToMinFloat32(x, y)
    x = convert(Array{Float32, 1}, x)
    y = convert(Array{Float32, 1}, y)
    z = convert(Array{Float32, 1}, vcat(x, y))

    posVal = filter(x -> x > 0 == true, z)
    negVal = filter(x -> x < 0 == true, z)
    
    posVal = sort(posVal) # max -> min
    negVal = sort(negVal, rev = true) # min -> max

    posSum = Float32(0.0)
    negSum = Float32(0.0)

    for i in eachindex(posVal)
        posSum = Float32(posSum + posVal[i])
    end
    for i in eachindex(negVal)
        negSum = Float32(negSum + negVal[i])
    end
    
    sum = Float32(posSum + negSum)

    println("minToMinFloat32: sum = ", sum)
end

function minToMinFloat64(x, y)
    x = convert(Array{Float64, 1}, x)
    y = convert(Array{Float64, 1}, y)
    z = convert(Array{Float64, 1}, vcat(x, y))

    posVal = filter(x -> x > 0 == true, z)
    negVal = filter(x -> x < 0 == true, z)
    
    posVal = sort(posVal) # max -> min
    negVal = sort(negVal, rev = true) # min -> max

    posSum = Float64(0.0)
    negSum = Float64(0.0)

    for i in eachindex(posVal)
        posSum = Float64(posSum + posVal[i])
    end
    for i in eachindex(negVal)
        negSum = Float64(negSum + negVal[i])
    end
    
    sum = Float64(posSum + negSum)

    println("minToMinFloat64: sum = ", sum)
end

Vx = [2.718281828,−(3.141592654),1.414213562,0.5772156649,0.3010299957]
Vy = [1486.2497,878366.9879,−(22.37492),4773714.647,0.000185049]
println("Zadanie 5\n")
println("A)")
forwardsFloat32(Vx, Vy)
forwardsFloat64(Vx, Vy)
println("\nB)")
backwardsFloat32(Vx, Vy)
backwardsFloat64(Vx, Vy)
println("\nC)")
maxToMaxFloat32(Vx, Vy)
maxToMaxFloat64(Vx, Vy)
println("\nD)")
minToMinFloat32(Vx, Vy)
minToMinFloat64(Vx, Vy)
