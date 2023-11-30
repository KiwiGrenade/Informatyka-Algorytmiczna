# Jakub Jaśków 268416
module Utils1
export ilorazyRoznicowe, warNewton, naturalna, rysujNnfx
using Plots

"""
Calc. difference quotient function

# Data:
x – vector of vertices x_0,...,x_n-1 (length n).        x[i] = x_{i-1}

f – vector of interpolaated function values (length n). f[i] = f(x_{i-1})

# Returns:
fx – vector of calculated diffrence quotients.          fx[i] = f[x_0, ..., x_{i-1}]
"""
function ilorazyRoznicowe(x::Vector{Float64}, f::Vector{Float64})
    n = length(x)
    fx = zeros(n)
    for i in 1:n
        fx[i] = f[i]
    end
    for j in 2:n
        for i in n:-1:j # 
            fx[i] = (fx[i] - fx[i - 1]) / (x[i] - x[i - j + 1])
        end
    end
    return fx
end


"""
Calc. value of interpolated polynomial in Newton's form

# Data:
x – vector of vertices x_0,...,x_n-1 (length n).        x[i] = x_{i-1}

fx – vector of calculated diffrence quotients.          fx[i] = f[x_0, ..., x_{i-1}]

t – point in which we want to calculate polynomial's value

# Returns:
nt – polynomial value in point t
"""
function warNewton(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    n = length(x)
    nt = fx[n]
    for i in (n - 1): -1: 1
        nt = fx[i] + (t - x[i]) * nt
    end
    return nt
end


"""
Calc. factors of the polynomial in natural form, given an interpolated polynomial in Newton's form

# Dane
x – vector of vertices x_0,...,x_n-1 (length n).        x[i] = x_{i-1}

fx – vector of calculated diffrence quotients.          fx[i] = f[x_0, ..., x_{i-1}]

# Wyniki
a – vector of calc. factors of polynomial in natural form. a[i] is factor at x^{i-1}
"""
function naturalna(x::Vector{Float64}, fx::Vector{Float64})
    n = length(x)
    a = zeros(n)
    a[n] = fx[n]
    for i in (n - 1): -1: 1
        a[i] = fx[i] - x[i] * a[i + 1]
        for j in (i + 1):(n - 1)
            a[j] += -x[i] * a[j + 1]
        end
    end
    return a
end


"""
Plot the interpolated polynomial and the interpolated function in interval
    [a, b] with n+1 points.
# Data:
f – function to interpolate

a, b – plotting interval

n – degree of the interpolated polynomial

# Returns:
p – plot
"""
function rysujNnfx(f,a::Float64,b::Float64,n::Int)
    x = zeros(n + 1)
    y = zeros(n + 1)
    step = (b - a) / n
    for k in 0:n
        x[k + 1] = a + k * step
        y[k + 1] = f(x[k + 1])
    end
    c = ilorazyRoznicowe(x, y)

    points = 50 * (n + 1)
    dx = (b - a) / (points - 1)
    xs = zeros(points)
    polynomial = zeros(points)
    function_ = zeros(points)
    xs[1] = a
    polynomial[1] = function_[1] = y[1]
    for i in 2:points
        xs[i] = xs[i - 1] + dx
        polynomial[i] = warNewton(x, c, xs[i])
        function_[i] = f(xs[i])
    end
    p = plot(xs, [polynomial function_], label=["polynomial" "function"], title="n (degree) = $n", palette = :Dark2_5,)
    display(p)
    return p
end

end