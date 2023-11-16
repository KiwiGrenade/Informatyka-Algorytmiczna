# Jakub Jaśków 268416
module Utils
export mbisekcji, mstycznych, msiecznych


"""
# Ex. 1
Bisection method - root finding method
# Data:
f – continuous function
a, b – interval ends,
epsilon, delta – precision.

# Returns
Four tuple (r, v, n_it, err):
r – approx. root of function f(x),
v – f(r),
n_it – number of iterations,
err – error:
        0 - all good,
        1 - no sign change in interval [a,b].
"""
function mbisekcji(f, a::Float64, b::Float64, delta::Float64, epsilon::Float64)
    A = f(a)
    B = f(b)

    if sign(A) == sign(B)
        return Nothing, Nothing, Nothing, 1
    end

    er = b - a
    n_it = 0

    while true
        n_it += 1
        er /= 2
        r = a + er
        v = f(r)

        if abs(er) < delta || abs(v) < epsilon
            return r, v, n_it, 0
        end

        if sign(v) != sign(A)
            b = r
            B = v
        else
            a = r
            A = v
        end
    end
end


"""
# Ex. 2
Newton-Raphson method - root finding method.

# Data:
f, pf – function f(x) and it's derivative f'(x),
x0 – initial guess for a root of f(x),
delta, epsilon – precision,
maxIt – maximum number of iterations.

# Returns
Four tuple (r, v, n_it, err):
r – approx. root of function f(x),
v – f(r),
n_it – number of iterations,
err – error:
        0 - all good,
        1 - desired precision hasn't been reached in maxIt iterations,
        2 - derievative is close to 0.
"""
function mstycznych(f, pf, x0::Float64, delta::Float64, epsilon::Float64, maxIt::Int)
    v = f(x0)
    if abs(v) < epsilon
        return x0, v, 0, 0
    end

    for n_it in 1:maxIt
        df = pf(x0)
        if abs(df) < epsilon
            return x0, v, n_it, 2
        end

        x1 = x0 - v/df
        v = f(x1)
        if abs(x1 - x0) < delta || abs(v) < epsilon
            return x1, v, n_it, 0
        end
        x0 = x1
    end
    return x0, v, maxIt, 1
end


"""
# Ex. 3
Secant method - root finding method.

# Dane
f – funkcja f(x) zadana jako anonimowa funkcja,
x0, x1 – approximations,
delta, epsilon – precision,
maxIt – maximum number of iterations.

# Returns
Four tuple (r, v, n_it, err):
r – approx. root of function f(x),
v – f(r),
n_it – number of iterations,
err – error:
        0 - all good,
        1 - no sign change in interval [a,b].
"""
function msiecznych(f, x0::Float64, x1::Float64, delta::Float64, epsilon::Float64, maxIt::Int)
    A = f(x0)
    B = f(x1)
    for n_it in 1:maxIt
        if abs(A) < abs(B)
            x0, x1 = x1, x0
            A, B = B, A
        end
        s = (x1 - x0)/(B - A)
        x0 = x1
        A = B
        x1 = x1 - A * s
        B = f(x1)
        if abs(x1 - x0) < delta || abs(B) < epsilon
            return x1, B, n_it, 0
        end
    end
    return x1, B, maxIt, 1
end

end