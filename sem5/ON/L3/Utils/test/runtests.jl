# Jakub Jaśków 268416
using Utils
using Test

@testset "Utils test" begin
    
    @testset "mbisekcji tests" begin
        include("mbisekcji_tests.jl")
    end
    
    @testset "mstycznych tests" begin
        include("mstycznych_tests.jl")
    end
    
    @testset "msiecznych tests" begin
        include("msiecznych_tests.jl")
    end
end
    