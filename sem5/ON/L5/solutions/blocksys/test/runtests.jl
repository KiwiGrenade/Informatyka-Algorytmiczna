# Jakub Jaśków 268416
include("../src/matrixgen.jl")
include("../src/blocksys.jl")
using .blocksys
using .matrixgen
using Test

########### UNIT Tests

# test_data = ["Dane16_1_1/", "Dane10000_1_1/", "Dane50000_1_1/", "Dane100000_1_1/", "Dane300000_1_1/", "Dane500000_1_1/"]
# print(test_data[1])

@testset "16x16" begin
    matrix = load_matrix("test_data/Dane16_1_1/A.txt")
    vec = load_vector("test_data/Dane16_1_1/b.txt")
    results = ones(16)

    @test isapprox(solve_gauss(matrix[1], vec[1], matrix[2], matrix[3]), results)

    matrix = load_matrix("test_data/Dane16_1_1/A.txt")
    vec = load_vector("test_data/Dane16_1_1/b.txt")
    @test isapprox(solve_gauss_with_choose(matrix[1], vec[1], matrix[2], matrix[3]),  results)
end

# @testset "10kx10k" begin
#     matrix = load_matrix("test_data/Dane10000_1_1/A.txt")
#     vec = load_vector("test_data/Dane10000_1_1/b.txt")
#     results = ones(10000)

#     @test isapprox(solve_gauss(matrix[1], vec[1], matrix[2], matrix[3]), results)

#     matrix = load_matrix("test_data/Dane10000_1_1/A.txt")
#     vec = load_vector("test_data/Dane10000_1_1/b.txt")
#     @test isapprox(solve_gauss_with_choose(matrix[1], vec[1], matrix[2], matrix[3]),  results)
# end

# @testset "50kx50k" begin
# matrix = load_matrix("test_data/Dane50000_1_1/A.txt")
# vec = load_vector("test_data/Dane50000_1_1/b.txt")
# results = ones(50000)

# @test isapprox(solve_gauss(matrix[1], vec[1], matrix[2], matrix[3]), results)

# matrix = load_matrix("test_data/Dane50000_1_1/A.txt")
# vec = load_vector("test_data/Dane50000_1_1/b.txt")
# @test isapprox(solve_gauss_with_choose(matrix[1], vec[1], matrix[2], matrix[3]),  results)
# end