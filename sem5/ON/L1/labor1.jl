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

println("Zadanie 1\n")
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