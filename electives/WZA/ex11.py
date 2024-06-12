from math import sqrt
import numpy as np
import matplotlib.pyplot as plt

theta = np.linspace(-100, 100, 19000)

r = np.sin(2 * theta)

x = (1-theta**2) / (1 + theta**2)
y = 2 * theta / (1 + theta**2)

plt.figure(figsize=(4, 4))
plt.plot(x, y, color='red')
plt.title("$x(t) = \\frac{1-t^2}{1+t^2}$, $y(t) = \\frac{2t}{1+t^2}$")
plt.show()


# x(t) = (1-t^2)/(1+t^2), y(t) = 2t/(1+t^2)
# x^2 + y^2 = ((1-t^2)^2+(2t)^2l) / (1+t^2)^2 = (t^4+2t^2+1)/(1+t^2)^2 = (1+t^2)^2/(1+t^2)^2 = 1
# Rozmaitosc ma punkt (-1, 0) a uklad rownan go nie ma
