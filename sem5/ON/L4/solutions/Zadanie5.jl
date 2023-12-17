# Jakub Jaśków 268416

include("Utils1/src/Utils1.jl")
using .Utils1
using Plots

f = x -> ℯ^x
g = x -> x^2 * sin(x)
for n in [5, 10, 15]
    plot_f = rysujNnfx(f, 0., 1., n)
    plot_g = rysujNnfx(g, -1., 1., n)
    savefig(plot_f, "plots/zadanie5F_$n.png")
    savefig(plot_g, "plots/zadanie5G_$n.png")
end
