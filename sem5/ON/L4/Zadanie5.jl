include("./Utils1/src/Utils1.jl")
using .Utils1

function zad5()
   
f = x -> ℯ^x
g = x -> x^2 * sin(x)
for n in [5, 10, 15]
    plot_f = rysujNnfx(f, 0., 1., n)
    plot_g = rysujNnfx(g, -1., 1., n)
end
end
zad5()