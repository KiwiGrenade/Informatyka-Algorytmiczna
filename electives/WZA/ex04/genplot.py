import numpy as np
from matplotlib import pyplot as plt

theta = np.linspace(0, 2 * np.pi, 1000)
r = np.sin(2 * theta)

fig = plt.figure()
ax = fig.add_subplot(polar=True)

theta = np.where(r >= 0, theta, theta + np.pi)
r = np.abs(r)
ax.plot(theta, r)
plt.show()
