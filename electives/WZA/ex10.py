from math import sqrt
import numpy as np
import matplotlib.pyplot as plt

u = np.linspace(-1, 1, 100)
v = np.linspace(-1, 1, 100)
U, V = np.meshgrid(u, v)

X_w = U
Y_w = U * V
Z_w = V**2

fig = plt.figure()
ax = fig.add_subplot(121, projection='3d')
ax.plot_surface(X_w, Y_w, Z_w, cmap='coolwarm', edgecolor='k')

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Whitney Umbrella')

x = np.linspace(-2, 2, 200)
y = np.linspace(-2, 2, 200)
X_v, Y_v = np.meshgrid(x, y)

Z_v = np.zeros_like(X_v)
mask = np.abs(Y_v) > 1e-6
Z_v[mask] = X_v[mask]**2 / Y_v[mask]**2

ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_surface(X_v, Y_v, Z_v, cmap='coolwarm', edgecolor='k')

ax2.set_xlabel('X')
ax2.set_ylabel('Y')
ax2.set_zlabel('Z')
ax2.set_title(r'Variety $x^2 - y^2z = 0$')

plt.show()


# 10.1
#   x = uv, y = v, z = u^2
#   GB=(u^2-z, ux-yz, uy-x, v-y, x^2-y^2z)I_3 = <x^2-y^2z>
#   u = x/v => z = u^2 = x^2/v^2 = x^2/y^2 => x^2-y^2z = 0
#   f = x^2-y^2

# 10.2
# (a,b,c) E C^3 and a^2-b^2c = 0
# więc (a, b, c, d, e) E C^5 takie, że: a=de, b=e, c=d^2, czyli e=b i d=sqrt(c)

# 10.3
# Przy zmianie C w R mamy: (0, 0, c) dla c > 0

# 10.4
# d/dx(f) = 2x
# d/dy(f) = -2yz
# d/dz(f) = -y^2
# x = 0, y = 0, z E REAL
