# Jakub Jaśków 268416

include("Utils1/src/Utils1.jl")
import .Utils1
using Plots

f = x -> abs(x)
g = x -> 1/(1+x^2)
for n in [5, 10, 15]
    plot_f = rysujNnfx(f, -1., 1., n)
    plot_g = rysujNnfx(g, -5., 5., n)
    savefig(plot_f, "plots/zadanie6F_$n.png")
    savefig(plot_g, "plots/zadanie6G_$n.png")
end