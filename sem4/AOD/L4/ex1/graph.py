#!/usr/bin/env python
import pandas as pd
import matplotlib.pyplot as plt

# Read the data from the CSV file
karp = pd.read_csv("./karp.csv")
dinic = pd.read_csv("./dinic.csv")

# Separate figures for each value
for value in ['time', 'maxflow', 'paths']:
    plt.figure()  # Create a new figure
    plt.scatter(karp['k'], karp[value], marker='o', label='Edmond-Karp')  # Plot the data
    plt.xlabel('k')  # Set the x-axis label
    if value == 'time':
        plt.ylabel('czas')  # Set the y-axis label
        plt.title(e'Wykres sredniego czasu wykonania od k [ms]')  # Set the title
    if value == 'maxflow':
        plt.ylabel('przeplyw')  # Set the y-axis label
        plt.title(e'Wykres sredniego maksymalnego przeplywu od k')  # Set the title
    if value == 'paths':
        plt.ylabel('liczba sciezek')  # Set the y-axis label
        plt.title(e'Wykres sredniej liczby sciezek od k')  # Set the title
    plt.legend()  # Add a legend
    plt.grid(True)  # Add grid lines
    plt.savefig('plots/karp_' + value + '.png')  # Show the figure