include("Utils1/src/Utils1.jl")
import .Utils1
f(x) = abs(x)
g(x) = 1.0 / (1.0 + x^2)

rysujNnfx(f, -1.0, 1.0, 5) 
rysujNnfx(f, -1.0, 1.0, 10)
rysujNnfx(f, -1.0, 1.0, 15)

rysujNnfx(g, -5.0, 5.0, 5)
rysujNnfx(g, -5.0, 5.0, 10)
rysujNnfx(g, -5.0, 5.0, 15)
