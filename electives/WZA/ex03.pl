import matplotlib.pyplot as plt
import numpy as np

from matplotlib import cm


def first_variety():
    plt.style.use('_mpl-gallery')
    X = np.arange(-5, 5, 0.25)
    Y = np.arange(-5, 5, 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = X ** 2 + Y ** 2

    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    ax.plot_surface(X, Y, Z, vmin=Z.min() * 2, cmap=cm.Oranges)

    plt.title(r'V($z -x^2 - y^2$)', y=1)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()


def second_variety():
    plt.style.use('_mpl-gallery')
    X = np.arange(-5, 5, 0.25)
    Y = np.arange(-5, 5, 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = np.sqrt(X ** 2 + Y ** 2)

    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    ax.plot_surface(X, Y, Z, vmin=Z.min() * 2, cmap=cm.Reds)

    plt.title(r'V($z^2 -x^2 - y^2$)', y=1)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()


def third_variety():
    plt.style.use('_mpl-gallery')
    X = np.arange(-5, 5, 0.25)
    Y = np.arange(-5, 5, 0.25)
    X, Y = np.meshgrid(X, Y)
    Z = X ** 2 - Y ** 2

    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    ax.plot_surface(X, Y, Z, vmin=Z.min() * 2, cmap=cm.Greens)
    plt.title(r'V($z -x^2 + y^2$)', y=1)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()


def fourth_variety():
    plt.style.use('_mpl-gallery')
    X = np.arange(-5, 5, 0.25)
    Y = np.zeros(int(10 / 0.25))
    Z = 0
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    plt.plot(X, Y, color='green')

    plt.title(r'V($xz, yz$)', y=1)
    Z = np.arange(-5, 5, 0.25)
    Y = np.arange(-5, 5, 0.25)
    Z, Y = np.meshgrid(Z, Y)
    X = 0

    ax.plot_surface(X, Y, Z, vmin=Z.min() * 2, cmap=cm.Blues)

    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    plt.show()


first_variety()
second_variety()
third_variety()
fourth_variety()
