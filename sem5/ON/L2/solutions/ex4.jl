# Jakub Jaśków 268416
using Polynomials
include("utils/wielomian.jl")

wNormal = Polynomial(reverse(p))
wProduct = fromroots(1:20)
wRoots = roots(wNormal)

dist1 = 3
dist2 = 20
dist3 = 25
dist4 = 10

println("\nZadanie 4")
println("########### A1 ###########")
println("A.1")
println(rpad("k", dist1),
        " & ", rpad("\$z_k\$", dist2), 
        " & ", rpad("\$|P(z_k)|\$", dist3), 
        " & ", rpad("\$|p(z_k)|\$", dist3), 
        " & ", rpad("\$|z_k - k|\$", dist3), 
        " \\\\\\hline")

for k in 1:20
    z_k = wRoots[k]
    println(rpad(k, dist1),
        " & ", rpad(z_k, dist2), 
        " & ", rpad(abs(wNormal(z_k)), dist3), 
        " & ", rpad(abs(wProduct(z_k)), dist3), 
        " & ", rpad(abs(z_k - k), dist3), 
        " \\\\\\hline")
end


println("########### A2 ###########")
println(rpad("k", dist1), 
        " & ", rpad("\$|P(k)|\$", dist3), 
        " & ", rpad("\$|p(k)|\$", dist4), 
        " \\\\\\hline")
for k in 1:20
    println(rpad(k, dist1), 
            " & ", rpad(abs(wNormal(k)), dist3), 
            " & ", rpad(abs(wProduct(k)), dist4), 
            " \\\\\\hline")
end

println("\n########### B ###########")

# disturb second factor of Wilkinson's polynomial
p[2] -= 2.0^(-23)

wNormalDistrbd = Polynomial(reverse(p))
wRootsDistrbd = roots(wNormalDistrbd)

dist2 = 42


println(rpad("k", dist1),
        " & ", rpad("\$z_k\$", dist2), 
        " & ", rpad("\$|P(z_k)|\$", dist3), 
        " & ", rpad("\$|p(z_k)|\$", dist3), 
        " & ", rpad("\$|z_k - k|\$", dist3), 
        " \\\\\\hline")

for k in 1:20
    z_k = wRootsDistrbd[k]
    println(rpad(k, dist1),
        " & ", rpad(z_k, dist2), 
        " & ", rpad(abs(wNormal(z_k)), dist3), 
        " & ", rpad(abs(wProduct(z_k)), dist3), 
        " & ", rpad(abs(z_k - k), dist3), 
        " \\\\\\hline")
end


