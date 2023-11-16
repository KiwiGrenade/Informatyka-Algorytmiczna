# Jakub Jaśków 268416
include("Utils/src/Utils.jl")
include("printResults.jl")

# Function pattern
f(x) = exp(x) - 3.0 * x

# Precision
delta = 10.0^-4.0
epsilon = 10.0^-4.0

println("#################################### --- X1 --- ####################################")
(r,v,it,err) = Utils.mbisekcji(f, 0.0, 1.0, delta, epsilon)
printResults(r, v, it, err)

println("\n#################################### --- X2 --- ####################################")
(r,v,it,err) = Utils.mbisekcji(f, 1.0, 2.0, delta, epsilon) # przedział (1,2)
printResults(r, v, it, err)
