# Jakub Jaśków 268416
include("../src/matrixgen.jl")
include("../src/blocksys.jl")
using .blocksys
using .matrixgen
using Test

test_case_list = ["Dane16_1_1/", "Dane10000_1_1/", "Dane50000_1_1/", "Dane100000_1_1/"]
n_list = [16, 10000, 50000, 100000, 300000, 500000]
for i in eachindex(test_case_list)
    test = test_case_list[i]
    @testset "$test" begin
        matrix = load_matrix("test_data/$test/A.txt")
        vec = load_vector("test_data/$test/b.txt")
        results = ones(n_list[i])

        @test isapprox(solve_gauss(matrix[1], vec[1], matrix[2], matrix[3]), results)

        matrix = load_matrix("test_data/$test/A.txt")
        vec = load_vector("test_data/$test/b.txt")
        @test isapprox(solve_gauss_with_choose(matrix[1], vec[1], matrix[2], matrix[3]),  results)
    end
end