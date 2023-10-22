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
        u = G.nodes[path[i]]
        v = G.nodes[path[i + 1]]

        coords = [u["coord"], v["coord"]]
        distance += math.dist(coords[0], coords[1])  # sum(dist(first_of, last of))

    distance += math.dist(G.nodes[path[-1]]["coord"], G.nodes[path[0]]["coord"])  # dist(last_of, first_of)
    return distance


def plot_data(G, path, file_name):
    path = path[:-1]  # cut off last element

    min_10_list = min_50_list = []
    min_10 = min_50 = min_1000 = math.inf
    for i in range(1, 1001):
        # permutate
        shuffle(path)

        cost = get_path_cost(G, path)

        min_1000 = min(min_1000, cost)
        min_50 = min(min_50, cost)
        min_10 = min(min_10, cost)
        if i % 10 == 0:
            min_10_list.append(min_10)
            min_10 = math.inf
        if i % 50 == 0:
            min_50_list.append(min_50)
            min_50 = math.inf
    print(min_1000)
    # Create a dot plot for the red data
    plt.plot(min_1000, 'ro', markersize=12, label='Red Dots')

    # Add blue dots to the same plot
    plt.plot(min_50_list, 'bo', markersize=8, label='Blue Dots')

    # Add yellow dots to the same plot
    plt.plot(min_10_list, 'yo', markersize=5, label='Yellow Dots')

    # Add labels and a title
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Dot Plot')

    # Add a legend
    plt.legend()

    # Display the plot
    plt.grid(True)  # Add a grid
    plt.savefig(f"graphs/{file_name}")
    plt.show()


def plot_path(G, path, file_name):
    path_graph = nx.path_graph(path, G)
    nx.draw(path_graph, node_size=7)
    plt.savefig(f'graphs/path_{file_name}')
    plt.show()


def plot_MST(G, file_name):
    # create MST, draw and save
    MST = nx.minimum_spanning_tree(G)
    nx.draw(MST, node_size=5)
    plt.savefig(f'graphs/MST_{file_name}.pdf')
    plt.show()


for file_name in os.listdir('inputs'):
    # load problem from .tsp file
    problem = tsp.load(f'inputs/{file_name}')
    # convert the problem to a networkx graph
    G = problem.get_graph()

    file_name = file_name[:-4]

    path = nx.algorithms.approximation.traveling_salesman_problem(G)
    # plot_MST(G, file_name)
    plot_path(G, path, file_name)
    # plot_data(G, path, file_name)
