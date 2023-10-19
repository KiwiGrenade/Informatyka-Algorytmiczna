# Jakub Jaśków
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
getMachEpsFloat32()
getMachEpsFloat64()
println("\nnextfloat<Float16>(0.0) = ", nextfloat(Float16(0.0)))
println("nextfloat<Float32>(0.0) = ", nextfloat(Float32(0.0)))
println("nextfloat<Float64>(0.0) = ", nextfloat(Float64(0.0)), '\n')
