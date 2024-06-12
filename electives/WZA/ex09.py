from math import sqrt
import numpy as np
import matplotlib.pyplot as plt

def draw_curve(func, rng, special_points, title):
    x = np.linspace(-rng, rng, 100)
    y = np.linspace(-rng, rng, 100)

    X, Y = np.meshgrid(x, y)
    Z = func(X, Y)

    plt.figure(figsize=(4, 4))
    plt.contour(X, Y, Z, levels=[0], colors='green')

    for point in special_points:
        plt.scatter(point[0], point[1], color='red')

    plt.title(title)
    plt.show()

from math import sqrt

def draw_curve(func, rng, special_points, title):
    x = np.linspace(-rng, rng, 100)
    y = np.linspace(-rng, rng, 100)

    X, Y = np.meshgrid(x, y)
    Z = func(X, Y)

    plt.figure(figsize=(4, 4))
    plt.contour(X, Y, Z, levels=[0], colors='red')

    for point in special_points:
        plt.scatter(point[0], point[1], color='blue')

    plt.title(title)
    plt.show()

draw_curve(lambda x, y: (x**2 + y**2 + 4*y)**2 - 16*(x**2 + y**2), 10, [(0,0)], '$(x^2 + y^2 + 4y)^2 - 16(x^2 + y^2) = 0$')
draw_curve(lambda x, y: 2*(x**2 + 9)*(y**2 - 16) + (x**2 - 9)**2 + (y**2 - 16)**2, 10, [(0, sqrt(7)), (0, -sqrt(7))], '$2(x^2 + 9)(y^2 - 16) + (x^2 - 9)^2 + (y^2 - 16)^2 = 0$')
draw_curve(lambda x, y: 350*x**2*y**2 - 15**2*(x**2 + y**2) + 12**2*(x**4 + y**4) + 81, 1.5, [], '$350x^2y^2 - 15^2(x^2 + y^2) + 12^2(x^4 + y^4) + 81 = 0$')


# 9.1:
#   1. x = 0 => y = 0 or y = -6
#   2. x^2 = -y^2-4y+8 => (-y^2-4y+8)(y+2)+y^2(y+6) = -y^3-4y^2+8y-2y^2-8y+16+y^3+6y^2=16!=0

# 9.2:
#   1. x = 0 => y = 0 or y = +/- sqrt(7) 
#   2. y = 0 => x = 0 or y = +/- 5

# 9.2:
#   1. x = 0 => y = 0 or y = +/- (5*sqrt(2))/8
#   2. y = 0 => x = 0 or y = +/- (5*sqrt(2))/8
