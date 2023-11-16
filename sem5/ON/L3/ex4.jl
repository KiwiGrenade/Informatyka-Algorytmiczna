# Jakub Jaśków 268416
include("Utils/src/Utils.jl")
include("printResults.jl")

# Function patterns
f(x) = sin(x) - (0.5 * x)^2.0
df(x) = cos(x) - 0.5 * x

# Precision
delta = 0.5 * 10.0^-5.0
epsilon = 0.5 * 10.0^-5.0
maxit = 32

println("Ex.4")
println("\nBissection method:")
(r,v,it,err) = Utils.mbisekcji(f, 1.5, 2.0, delta, epsilon)
printResults(r, v, it, err)

println("\nNewton-Rhapson method:")
(r,v,it,err) = Utils.mstycznych(f, df, 1.5, delta, epsilon, maxit)
printResults(r, v, it, err)

println("\nSecant method:")
(r,v,it,err) = Utils.msiecznych(f, 1.0, 2.0, delta, epsilon, maxit)
printResults(r, v, it, err)