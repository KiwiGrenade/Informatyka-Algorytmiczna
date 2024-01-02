# Jakub Jaśków
include("blocksys/src/blocksys.jl")
include("blocksys/src/matrixgen.jl")
using .blocksys
using .matrixgen
using Plots

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
plot(mat_sizes, [times_gauss times_gauss_choose], label=["Gauss" "Gauss with choose"], linewidth=[3 3])
png("plots/times_solving")
# Memory
plot(mat_sizes, [memory_gauss memory_gauss_choose], label=["Gauss" "Gauss with choose"], linewidth=[3 3])
png("plots/memory_solving")
# Operations
plot(mat_sizes, [operations_gauss operations_gauss_choose], label=["Gauss" "Gauss with choose"], linewidth=[3 3])
png("plots/operations_solving")

rm("test_matrix.txt")
