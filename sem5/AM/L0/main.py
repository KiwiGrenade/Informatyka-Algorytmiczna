import os
import sys
import matplotlib.pyplot as plt
import networkx as nx
import tsplib95 as tsp
from numpy.random import shuffle
import math

def get_path_cost(G, path):
    distance = 0
    for i in range(len(path) - 1):
        distance += G.edges[path[i], path[i+1]]["weight"]
    # add cost of return path
    distance += G.edges[path[0], path[-1]]["weight"]

    return distance

def get_minimums(G, path):
    print("Getting minimums...")
    path = path[:-1]  # cut off last element

    min_10_list_y = []
    min_10_list_x = []
    min_50_list_y = []
    min_50_list_x = []
    min_10_x = 0
    min_10_y = math.inf
    min_50_x = 0
    min_50_y = math.inf
    min_1000_x = 0
    min_1000_y = math.inf
    for i in range(1, 1001):
        # permutate
        shuffle(path)

        cost = get_path_cost(G, path)
        if cost < min_10_y:
            min_10_x = i
            min_10_y = cost
        if cost < min_50_y:
            min_50_x = i
            min_50_y = cost
        if cost < min_1000_y:
            min_1000_x = i
            min_1000_y = cost
        if i % 10 == 0:
            min_10_list_y.append(min_10_y)
            min_10_list_x.append(min_10_x)
            min_10_y = math.inf
        if i % 50 == 0:
            min_50_list_y.append(min_50_y)
            min_50_list_x.append(min_50_x)
            min_50_y = math.inf
    min_10_list = [min_10_list_x, min_10_list_y]
    min_50_list = [min_50_list_x, min_50_list_y]
    min_1000 = [min_1000_x, min_1000_y]
    return min_10_list, min_50_list, min_1000


def plot_data(min_10_list, min_50_list, min_1000, file_name):
    print(f'Plotting min_{file_name}...')

    # Create a dot plot for the red data
    plt.scatter(min_1000[0], min_1000[1], c="red", s=150, label='1000 Minimum')

    # Add blue dots to the same plot
    plt.scatter(min_50_list[0], min_50_list[1],c="orange", s= 40, label='50 Minimum')

    # Add yellow dots to the same plot
    plt.scatter(min_10_list[0], min_10_list[1], c="blue", s = 8,label='10 Minimum')

    # Add labels and a title
    plt.title(file_name)

    # Add a legend
    plt.legend()

    # Display the plot
    plt.grid(True)  # Add a grid
    plt.savefig(f"graphs/min_{file_name}")
    plt.show()


def plot_path(G, path, file_name):
    print(f'Plotting path_{file_name}...')
    path_graph = nx.path_graph(path, G)
    nx.draw(path_graph, node_size=7)
    plt.savefig(f'graphs/path_{file_name}')
    plt.show()


def plot_MST(G, file_name):
    print(f'Plotting MST{file_name}...')
    # create MST, draw and save
    MST = nx.minimum_spanning_tree(G)
    nx.draw(MST, node_size=5)
    plt.savefig(f'graphs/MST_{file_name}')
    plt.show()

for file_name in os.listdir('inputs'):
    # load problem from .tsp file
    # file_name = "xqf131.tsp"
    problem = tsp.load(f'inputs/{file_name}')
    # convert the problem to a networkx graph
    G = problem.get_graph()

    file_name = file_name[:-4]

    print("Getting path...")
    path = nx.algorithms.approximation.traveling_salesman_problem(G)
    path = path[:-1]
    # plot_MST(G, file_name)
    # plot_path(G, path, file_name)
    min_10_list, min_50_list, min_1000 = get_minimums(G, path)
    plot_data(min_10_list, min_50_list, min_1000, file_name)
