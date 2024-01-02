# Jakub Jaśków
include("blocksys/src/blocksys.jl")
include("blocksys/src/matrixgen.jl")
using .blocksys
using .matrixgen
using PyPlot

# Sizes of matrices to generate
mat_sizes = [1000, 2000, 5000, 10000, 20000, 25000, 30000, 50000]
sub_size = 4
cond = Float64(1.0)

# Tests results
times_gauss = zeros(length(mat_sizes))
times_gauss_choose = zeros(length(mat_sizes))

memory_gauss = zeros(length(mat_sizes))
memory_gauss_choose = zeros(length(mat_sizes))

operations_gauss = zeros(length(mat_sizes))
operations_gauss_choose = zeros(length(mat_sizes))


for i = 1:length(mat_sizes)

    # Generating matrix for tests
    blockmat(mat_sizes[i], sub_size, cond, "test_matrix.txt")
    println("Matrix size: ", mat_sizes[i])
    println("Submatrices size: ", sub_size)

    # Loading generated matrix and computing vector of right sides
    matrix = load_matrix("test_matrix.txt")
    vec = generate_right_side_vector(matrix[1], matrix[2], matrix[3])

    #### Gauss
    results = @timed solve_gauss(matrix[1], vec, matrix[2], matrix[3])
    
    times_gauss[i] = results[2] 
    memory_gauss[i] = results[3]
    operations_gauss[i] = mat_sizes[i] * sub_size^2 + 2 * mat_sizes[i]

    # Loading generated matrix and computing vector of right sides
    matrix = load_matrix("test_matrix.txt")
    vec = generate_right_side_vector(matrix[1], matrix[2], matrix[3])

    #### Gauss with choose
    results = @timed solve_gauss_with_choose(matrix[1], vec, matrix[2], matrix[3])
    
    times_gauss_choose[i] = results[2]
    memory_gauss_choose[i] = results[3]
    operations_gauss_choose[i] = mat_sizes[i] * sub_size^3 + 2 * mat_sizes[i]
end

#### Solving
### Plots
# Time
clf()
plot(mat_sizes, times_gauss, label="Gauss", linewidth=1.0)
plot(mat_sizes, times_gauss_choose, label="Gauss with choose", linewidth=1.0)
grid(true)
legend(loc=2,borderaxespad=0)
title("Calculation time")
savefig("../plots/times_solving.png")

# Memory
clf()
plot(mat_sizes, memory_gauss, label="Gauss", linewidth=1.0)
plot(mat_sizes, memory_gauss_choose, label="Gauss with choose", linewidth=1.0)
grid(true)
legend(loc=2,borderaxespad=0)
title("Used memory")
savefig("../plots/memory_solving.png")

# Operations
clf()
plot(mat_sizes, operations_gauss, label="Gauss", linewidth=1.0)
plot(mat_sizes, operations_gauss_choose, label="Gauss with choose", linewidth=1.0)
grid(true)
legend(loc=2,borderaxespad=0)
title("Number of operations")
savefig("../plots/operations_solving.png")
