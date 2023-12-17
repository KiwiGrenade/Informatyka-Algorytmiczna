# Jakub Jaśków 268416
include("Utils/src/Utils.jl")
include("printResults.jl")

# Function patterns
f(x) = exp(1.0 - x) - 1.0
g(x) = x * exp(-x)

# Derievatives
df(x) = -exp(1.0 - x)
dg(x) = exp(-x) - x * exp(-x)

# Precision
delta = 10.0^-5.0
epsilon = 10.0^-5.0
maxit = 64

println("#################################### --- y = e^(1-x)-1 --- ####################################")
println("Bissection method:")
(r,v,it,err) = Utils.mbisekcji(f, 0.0, 1.5, delta, epsilon)
printResults(r, v, it, err)

println("\nNewton-Rhapson method:")
(r,v,it,err) = Utils.mstycznych(f, df, 0.5, delta, epsilon, maxit)
printResults(r, v, it, err)

println("\nSecant method:")
(r,v,it,err) = Utils.msiecznych(f, -1.0, 2.0, delta, epsilon, maxit)
printResults(r, v, it, err)


println("\n\n\n#################################### --- y = xe^-x --- ####################################")
println("Bissection method:")
(r,v,it,err) = Utils.mbisekcji(g, -0.5, 1.0, delta, epsilon)
printResults(r, v, it, err)

println("\nNewton-Rhapson method:")
(r,v,it,err) = Utils.mstycznych(g, dg, -0.5, delta, epsilon, maxit)
printResults(r, v, it, err)

println("\nSecant method:")
(r,v,it,err) = Utils.msiecznych(g, -1.0, 0.5, delta, epsilon, maxit)
printResults(r, v, it, err)