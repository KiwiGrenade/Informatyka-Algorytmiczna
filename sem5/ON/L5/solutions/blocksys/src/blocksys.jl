# Jakub Jaśków 268416

module blocksys
using SparseArrays
"""
Reads matrix data from file.

Parameters:
filepath - path to input file

Return: 
(A, n, l) - tuple: A - matrix; n - size of matrix A; l - size of submatrices
"""

export load_matrix
export load_vector
export write_results
export generate_right_side_vector
export solve_gauss
export gauss_with_choose
export solve_gauss_with_choose

function load_matrix(filepath::String)
    local data = C_NULL
    open(filepath, "r") do file
        sizes = split(readline(file), " ")
        n = parse(Int64, sizes[1])
        l = parse(Int64, sizes[2])

        # Matrix A
        A = spzeros(Float64, n, n)
        for line in eachline(file)
            data = split(line, " ")
            i = parse(Int64, data[1])
            j = parse(Int64, data[2])
            value = parse(Float64, data[3])

            A[j, i] = value
        end
        data = (A, n, l)
    end
    return data
end


"""
Reads vector of right sides

Parameters:
filepath - is path to file with data; is String

Return:
(b, n) - tuple: b - vector of right sides; n size of vector b
"""
function load_vector(filepath::String)
    local data = C_NULL
    open(filepath, "r") do file
        n = parse(Int64, readline(file))
        # Vector b
        b = zeros(n)
        i = 1
        for line in eachline(file)
            b[i] = parse(Float64, line)
            i += 1
        end
        data = (b, n)
    end
    return data
end


"""
Writes results of computations to file.

Parameters:
filpath - path to file where results should be saved; is String
x - vector with arguments; is Vector{Float64}
n - length of given vector x; is Int64
is_b_gen - determinates type of b vector: if true b was generated, false - b was read from file

Return:
Nothing is retruned.
"""
function write_results(filepath::String, x::Vector{Float64}, n::Int64, is_b_gen::Bool)
    local err::Float64
    open(filepath, "w") do file
        if is_b_gen 
            x_initial = ones(n)

            err = norm(x_initial - x) / norm(x)
            println(file, err)
        end

        for i = 1:n
            println(file, x[i])
        end
    end
end


"""
Genrates right sides vector for given matrix.

Parameters:
A - matrix; is Sparse Matrix; is SparseMatrixCSC{Float64, Int64}
n - size of matrix A; is Int64
l - size of submatrices of A; is Int64

Returns:
b - generated vector b; is Vector{Float64}
"""
function generate_right_side_vector(A::SparseMatrixCSC{Float64, Int64}, n::Int64, l::Int64)
    b = zeros(n)
    for i = 1:n
        b[i] = Float64(0.0)
        for j = max(1, Int64(l * floor((i - 1) / l)) - 1):min(n, Int64(l + l * floor((i - 1) / l)))
            b[i] += A[j, i]
        end 

        if i + l <= n
            b[i] += A[i, i + l]
        end
    end
    return b
end


"""
Makes gaussian eleimination on given matrix. 
If is_lu is set function makes LU decompsition using gaussian elimiantion.

Parameters:
A - matrix; is Sparse Matrix; is SparseMatrixCSC{Float64, Int64}
b - vector with values; is Vector{Float64}
n - size of matrix A; is Int64
l - size of submatrices of A; is Int64
is_lu - detrminates if function should be used: to LU decomposition if true; to only gauss elimination oth.

Return:
(A, b) - tuple: A - given matrix after elimination, is SparseMatrixCSC{Float64, Int64};
                b - given vector of right sides after elimination, is Vector{Float64}
"""
function gauss(A::SparseMatrixCSC{Float64, Int64}, b::Vector{Float64}, n::Int64, l::Int64, is_lu::Bool)
    # Iteration trough columns
    for k = 1:n - 1

        # Elements to eliminate in current column
        to_eliminate = k + (l - k % l)
        #to_eliminate = convert(Int64, min(l + l * floor((k+1) / l), n))

        # Iteration trough elements to eliminate
        for i = k + 1:to_eliminate

            # Multiplier = element to eliminate / current element on diagonal
            multiplier = A[k, i] / A[k, k]

            if is_lu
                # If it's LU decomposition set here used multiplier
                A[k, i] = multiplier
            else
                A[k, i] = Float64(0.0)
            end

            # Iteration trough columns
            for j = k + 1:min(k + l, n)
                A[j, i] -= multiplier * A[j, k]
            end

            # If it's LU it's unnecessarry
            if !is_lu
                b[i] -= multiplier * b[k]
            end
        end
    end

    return (A, b)
end


"""
Solves set of linear equations using gaussian elimination method.

Parameters:
A - matrix; is Sparse Matrix; is SparseMatrixCSC{Float64, Int64}
b - vector with values; is Vector{Float64}
n - size of matrix A; is Int64
l - size of submatrices of A; is Int64

Return:
x - vector with solutions; if Vector{Float64}
"""
function solve_gauss(A::SparseMatrixCSC{Float64, Int64}, b::Vector{Float64}, n::Int64, l::Int64)
    res = gauss(A, b, n, l, false)
    _A = res[1]
    _b = res[2]
    # Vector with solutions of equations set
    x = zeros(n)
    # Iteration trough rows
    for i = n:-1:1
        sum_from_row = Float64(0.0)
        #Iteration trough columns
        for j = i + 1:min(n, i + l)
            sum_from_row += _A[j, i] * x[j]
        end
        x[i] = (_b[i] - sum_from_row) / _A[i, i]
    end
    return x
end


"""
Makes gaussian eleimination with choose of main element on given matrix. 
If is_lu is set function makes LU decompsition using gaussian elimiantion with choose of main element.

Parameters:
A - matrix; is Sparse Matrix; is SparseMatrixCSC{Float64, Int64}
b - vector with values; is Vector{Float64}
n - size of matrix A; is Int64
l - size of submatrices of A; is Int64
is_lu - detrminates if function should be used: to LU decomposition if true; to only gauss elimination oth.

Return:
(A, perm, b) - tuple: A - given matrix after elimination, is SparseMatrixCSC{Float64, Int64};
                perm - permutation vector, is Vector{Float64};
                b - given vector of right sides after elimination, is Vector{Float64}
"""
function gauss_with_choose(A::SparseMatrixCSC{Float64, Int64}, b::Vector{Float64}, n::Int64, l::Int64, is_lu::Bool)
    # Permutation vector
    perm = zeros(Int64, n)

    # Put not permutated sequence into perm
    for i = 1:n
        perm[i] = i
    end

    # Iteration trough columns
    for k = 1:n - 1
        # Elements to eliminate in current column
        to_eliminate = k + (l - k % l)
        # Row with maximal element
        max_row = k
        # Maximal element in column
        max_element = abs(A[k, k])

        for i = k:to_eliminate
            if abs(A[k, perm[i]]) > max_element
                max_element = abs(A[k, perm[i]])
                max_row = i
            end
        end
        
        perm[k], perm[max_row] = perm[max_row], perm[k]

        # Iteration trough elements to eliminate
        for i = k + 1:to_eliminate
            multiplier = A[k, perm[i]] / A[k, perm[k]]

            if is_lu
                A[k, perm[i]] = multiplier
            else
                A[k, perm[i]] = Float64(0.0)
            end

            # Iteration trough columns
            for j = k + 1:min(k + 2 * l, n)
                A[j, perm[i]] -= multiplier * A[j, perm[k]]
            end

            if !is_lu
                b[perm[i]] -= multiplier * b[perm[k]]
            end
        end 
    end

    return (A, perm, b)
end


"""
Solves set of linear equations using gaussian elimination method with choose of main element

Parameters:
A - matrix; is Sparse Matrix; is SparseMatrixCSC{Float64, Int64}
b - vector with values; is Vector{Float64}
n - size of matrix A; is Int64
l - size of submatrices of A; is Int64

Return:
x - vector with solutions; if Vector{Float64}
"""
function solve_gauss_with_choose(A::SparseMatrixCSC{Float64, Int64}, b::Vector{Float64}, n::Int64, l::Int64)
    res = gauss_with_choose(A, b, n, l, false)
    _A = res[1]
    _perm = res[2]
    _b = res[3]
    #Vector with solutions of equations set
    x = zeros(n)

    # Iteration trough rows
    for i = n:-1:1
        sum_from_row = Float64(0.0)

        #Iteration trough columns
        for j = i + 1:min(i + 2 * l + 1, n)
            sum_from_row += _A[j, _perm[i]] * x[j]
        end

        x[i] = (_b[_perm[i]] - sum_from_row) / _A[i, _perm[i]]
    end
    return x
end

end # module end