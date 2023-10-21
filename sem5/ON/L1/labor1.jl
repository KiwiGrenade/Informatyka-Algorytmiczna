# Jakub Jaśków

# Zadanie 1

function getMachEpsFloat16()
    machinEps = Float16(1.0)
    while(Float16(Float16(1.0) + machinEps) != Float16(1.0))
        machinEps = Float16(machinEps / Float16(2.0))
    end
    println("Float16 machine epsilon: ", machinEps)    
end

function getMachEpsFloat32()
    machinEps = Float32(1.0)
    while(Float32(Float32(1.0) + machinEps) != Float32(1.0))
        machinEps = Float32(machinEps / Float32(2.0))
    end
    println("Float32 machine epsilon: ", machinEps)    
end

function getMachEpsFloat64()
    machinEps = Float64(1.0)
    while(Float64(Float64(1.0) + machinEps) != Float64(1.0))
        machinEps = Float64(machinEps / Float64(2.0))
    end
    println("Float64 machine epsilon: ", machinEps)    
end

println("Zadanie 1.1\n")
getMachEpsFloat16()
println("eps(Float16) = ", eps(Float16))
getMachEpsFloat32()
println("eps(Float32) = ", eps(Float32))
getMachEpsFloat64()
println("eps(Float64) = ", eps(Float64))
println()

function getEtaFloat16()
    eta = Float16(1.0)
    while(Float16(eta/2.0) > 0.0)
        eta = Float16(eta / 2.0)
    end
    println("Eta Float16 = ", eta)
end

function getEtaFloat32()
    eta = Float32(1.0)
    while(Float32(eta/2.0) > 0.0)
        eta = Float32(eta / 2.0)
    end
    println("Eta Float32 = ", eta)
end

function getEtaFloat64()
    eta = Float64(1.0)
    while(Float64(eta/2.0) > 0.0)
        eta = Float64(eta / 2.0)
    end
    println("Eta Float64 = ", eta)
end

println("Zadanie 1.2\n")
getEtaFloat16()
println("Eta nextfloat<Float16>(0.0) = ", nextfloat(Float16(0.0)))
getEtaFloat32()
println("Eta nextfloat<Float32>(0.0) = ", nextfloat(Float32(0.0)))
getEtaFloat64()
println("Eta nextfloat<Float64>(0.0) = ", nextfloat(Float64(0.0)))
println()

function maxIterFloat16()
    max = Float16(1.0)
    while isinf(Float16(max * 2.0)) == false
        max *= Float16(2.0)
    end
    println("maxFloat16 = ", max)
end

function maxIterFloat32()
    max = Float32(1.0)
    while isinf(Float32(max * 2.0)) == false
        max *= Float32(2.0)
    end
    println("maxFloat32 = ", max)
end

function maxIterFloat64()
    max = Float64(1.0)
    while isinf(Float64(max * 2.0)) == false
        max *= Float64(2.0)
    end
    println("maxFloat64 = ", max)
end

println("Zadanie 1.3\n")
maxIterFloat16()
println("floatmax(Float16) = ", floatmax(Float16))
maxIterFloat32()
println("floatmax(Float32) = ", floatmax(Float32))
maxIterFloat64()
println("floatmax(Float64) = ", floatmax(Float64))
println()

# Zadanie 2

println("Zadanie 2\n")
println("1 - 3(4/3-1) = ", Float16(1.0 - 3.0*Float16(Float16(4.0 / 3.0) - 1.0)))
println("macheps(Float16) = ", eps(Float16))
println("1 - 3(4/3-1) = ", Float32(1.0 - 3.0*Float32(Float32(4.0 / 3.0) - 1.0)))
println("macheps(Float32) = ", eps(Float32))
println("1 - 3(4/3-1) = ", Float64(1.0 - 3.0*Float64(Float64(4.0 / 3.0) - 1.0)))
println("macheps(Float64) = ", eps(Float64))
println()

# Zadanie 3

println("Zadanie 3\n")
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

println()

# Zadanie 4

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
println()

println("Zadanie 5\n")

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
println()

println("Zadanie 6\n")

function f(x)
    result = Float64(sqrt(Float64(Float64(x^2.0)+1.0))-1.0)
    println("f(", x, ") = ", result)
end

function g(x)
    x2 = Float64(x^2.0)
    result = Float64(x2 / Float64(sqrt(Float64(x2 + 1.0))+1.0))
    println("g(", x, ") = ", result)
end

for c = 1:10
    f(8^((-1.0) * c))
end
println()
for c = 1:10
    g(8^((-1.0) * c))
end

println()

println("Zadanie 7\n")

function f(x)
    return Float64(Float64(sin(x)) + Float64(cos(3.0 * x)))
end

for n = 0 : 54
    h = Float64(2.0 ^ ((-1.0 * n)))
    x_0 = Float64(1.0)
    fDev = Float64(Float64(f(Float64(x_0 + h)) - f(x_0)) / h)
    println("f`(", x_0, ") = ", fDev, ", h = ", h)
end

println()
