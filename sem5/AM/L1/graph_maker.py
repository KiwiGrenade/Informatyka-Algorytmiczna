import matplotlib.pyplot as plt


def read_points(testcase_name):
    with open("examples/{}.tsp".format(testcase_name), "r") as file:
        lines = [line.strip() for line in file.readlines()]
        proper_lines = lines[lines.index("NODE_COORD_SECTION") + 1:lines.index("EOF")]
        proper_lines = [line.split() for line in proper_lines]

        points = [[0, 0]]
        for line in proper_lines:
            points.append([int(line[1]), int(line[2])])

        return points


def read_mst(testcase_name):
    with open("results/{}-mst.txt".format(testcase_name), "r") as file:
        lines = [line.strip() for line in file.readlines()]
        proper_lines = [line.split() for line in lines[2:] if line != ""]

        weight = int(lines[0].split()[1])
        edges = []
        for line in proper_lines:
            edges.append([int(line[0]), int(line[1])])

        return weight, edges


def read_tsp_cycle(testcase_name):
    with open("results/{}-tsp-mst.txt".format(testcase_name), "r") as file:
        lines = [line.strip() for line in file.readlines()]
        proper_lines = [line.split()[0] for line in lines[2:] if line != ""]

        weight = int(lines[0].split()[1])
        edges = []
        n = len(proper_lines)
        for line_index in range(n):
            edges.append([int(proper_lines[line_index]), int(proper_lines[(line_index + 1) % n])])

        return weight, edges


def read_random_cycle_weights(testcase_name):
    with open("results/{}-rand.txt".format(testcase_name), "r") as file:
        cycle_weights = [int(line.strip()) for line in file.readlines()]

        return cycle_weights


def read_local_search_results(testcase_name, method_name):
    with open("results/{}-{}.txt".format(testcase_name, method_name), "r") as file:
        lines = [line.strip().split() for line in file.readlines()]
        improvements = []
        initial_cycle_weights = []
        final_cycle_weights = []
        cycles = []

        cycle = []
        for line in lines:
            if len(line) == 2 and line[0] == "improvements:":
                improvements.append(int(line[1]))
            elif len(line) == 2 and line[0] == "initial-cycle-weight:":
                initial_cycle_weights.append(int(line[1]))
            elif len(line) == 2 and line[0] == "final-cycle-weight:":
                final_cycle_weights.append(int(line[1]))
            elif len(line) == 1:
                cycle.append(int(line[0]))
            elif len(line) == 0:
                cycles.append(cycle)
                cycle = []

        return improvements, initial_cycle_weights, final_cycle_weights, cycles


def draw_simple_plot(x, ys, labels, colors, x_label, y_label, plot_averages, plot_title, output_file_name):
    plt.clf()

    for y, label, color in zip(ys, labels, colors):
        plt.scatter(x, y, label=label, color=color, marker="o")

    if plot_averages:
        avgs = [sum(y) / len(y) for y in ys]

        for avg, label, color in zip(avgs, labels, colors):
            plt.axhline(y = avg, label="{}-average({})".format(label, int(avg)), color=color, linestyle="-")

    plt.legend(bbox_to_anchor=(1.05, 1.0), loc="upper left")
    plt.title(plot_title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(output_file_name, bbox_inches="tight")


def draw_path(points, edges, plot_title, output_file_name):
    plt.clf()

    points_x = [point[0] for point in points[1:]]
    points_y = [point[1] for point in points[1:]]
    plt.scatter(points_x, points_y, [15 for _ in range(len(points_x))], color="orange", marker="o")

    for edge in edges:
        xs = [points[edge[0]][0], points[edge[1]][0]]
        ys = [points[edge[0]][1], points[edge[1]][1]]
        plt.plot(xs, ys, color="black")

    plt.title(plot_title)
    plt.axis("off")
    plt.savefig(output_file_name, bbox_inches="tight")


def draw_random_cycle_stats(cycle_weights, plot_title, output_file_name):
    plt.clf()

    series10 = [cycle_weights[i:i + 10] for i in range(0, len(cycle_weights), 10)]
    series50 = [cycle_weights[i:i + 50] for i in range(0, len(cycle_weights), 50)]

    min_series_10 = [min(serie) for serie in series10]
    min_series_50 = [min(serie) for serie in series50]

    avg_series_10 = sum(min_series_10) / len(min_series_10)
    avg_series_50 = sum(min_series_50) / len(min_series_50)

    min_weight = min(cycle_weights)

    print("{}: min={}  avg10={}  avg50={}".format(plot_title, min_weight, avg_series_10, avg_series_50))

    reps10 = [rep for rep in range(10, len(cycle_weights) + 1, 10)]
    reps50 = [rep for rep in range(50, len(cycle_weights) + 1, 50)]

    plt.scatter(reps10, min_series_10, marker="o", color="orange")
    plt.scatter(reps50, min_series_50, marker="o", color="black")

    plt.axhline(y = avg_series_10, color="orange", linestyle="-", label="avg of min of 10")
    plt.axhline(y = avg_series_50, color="black", linestyle="-", label="avg of min of 50")
    plt.axhline(y = min_weight, color="red", linestyle="-", label="minimum")

    plt.legend(bbox_to_anchor=(1.05, 1.0), loc="upper left")
    plt.title(plot_title)
    plt.xlabel("cycle number")
    plt.ylabel("cycle total weight")
    plt.savefig(output_file_name, bbox_inches="tight")


def draw_local_search_stats(improvements, initial_weights, final_weights, plot_title, output_file_name):
    plt.clf()

    repetitions = list(range(len(improvements)))
    improvements_avg = sum(improvements) / len(improvements)
    final_weights_avg = sum(final_weights) / len(final_weights)
    best_final_weight = min(final_weights)

    plt.scatter(repetitions, initial_weights, marker="o", color="black", label="initial cycle")
    plt.scatter(repetitions, final_weights, marker="o", color="orange", label="final cycle")
    plt.axhline(y = final_weights_avg, color="magenta", linestyle="-", label="average final weights sum\n({})".format(int(final_weights_avg)))
    plt.axhline(y = best_final_weight, color="red", linestyle="-", label="best final weights sum\n({})".format(int(best_final_weight)))

    plt.legend(bbox_to_anchor=(1.05, 1.0), loc="upper left")
    plt.title(plot_title)
    plt.xlabel("repetition number")
    plt.ylabel("cycle total weight")
    plt.savefig(output_file_name, bbox_inches="tight")


def process_local_search(testcase_name, points, improvements, initial_weights, final_weights, cycles, method_name, filename_sufix):
    best_cycle_index = final_weights.index(min(final_weights))
    best_cycle_improvements = improvements[best_cycle_index]
    best_cycle_initial_weight = initial_weights[best_cycle_index]
    best_cycle_final_weight = final_weights[best_cycle_index]
    cycle_average_weight = sum(final_weights) / len(final_weights)
    cycle_average_improvements = sum(improvements) / len(improvements)
    best_cycle = cycles[best_cycle_index]

    cycle_edges = []
    for index in range(len(best_cycle)):
        cycle_edges.append([best_cycle[index], best_cycle[(index + 1) % len(best_cycle)]])

    print("TSP cycle for {} and {}: best={}  avg={}  imp={}".format(testcase_name, method_name, best_cycle_final_weight, cycle_average_weight, cycle_average_improvements))

    draw_path(points, cycle_edges,
        "TSP cycle for {};\n{}; total weight = {}".format(testcase_name, method_name, best_cycle_final_weight), "plots/{}-{}.png".format(testcase, filename_sufix))

    draw_local_search_stats(improvements, initial_weights, final_weights, 
        "TSP cycle for {};\n{}".format(testcase_name, method_name), "plots/{}-{}-stats.png".format(testcase, filename_sufix))


TESTCASES = [
    "xqf131", "xqg237", "pma343", "pka379", "bcl380",
    "pbl395", "pbk411", "pbn423", "pbm436", "xql662",
    "xit1083", "icw1483", "djc1785", "dcb2086", "pds2566"
]


for testcase in TESTCASES:
    points = read_points(testcase)
    mst_weigth, mst_edges = read_mst(testcase)
    tsp_cycle_weight, tsp_cycle_edges = read_tsp_cycle(testcase)
    random_cycle_weights = read_random_cycle_weights(testcase)
    ls1_imp, ls1_iw, ls1_fw, ls1_cyc = read_local_search_results(testcase, "local-search-mst")
    ls2_imp, ls2_iw, ls2_fw, ls2_cyc = read_local_search_results(testcase, "local-search-rand")
    ls3_imp, ls3_iw, ls3_fw, ls3_cyc = read_local_search_results(testcase, "local-search-rand-rand-neighbourhood")

    draw_path(points, mst_edges,
        "MST for {}; total weight = {}".format(testcase, mst_weigth), "plots/{}-mst.png".format(testcase))

    draw_path(points, tsp_cycle_edges,
        "TSP cycle based on MST for {}; total weight = {}".format(testcase, tsp_cycle_weight), "plots/{}-tsp-mst.png".format(testcase))

    draw_random_cycle_stats(random_cycle_weights, "Random cycles weight for {}".format(testcase), "plots/{}-rand.png".format(testcase))

    print("TSP cycle based on MST for {}: {}".format(testcase, tsp_cycle_weight))

    process_local_search(testcase, points, ls1_imp, ls1_iw, ls1_fw, ls1_cyc, 
        "Local Search with initial MST solution", "tsp-ls-mst")

    process_local_search(testcase, points, ls2_imp, ls2_iw, ls2_fw, ls2_cyc, 
        "Local Search with initial random solution", "tsp-ls-rand")

    process_local_search(testcase, points, ls3_imp, ls3_iw, ls3_fw, ls3_cyc, 
        "Local Search with initial random solution and random neighbourhood", "tsp-ls-rand-rand")

    min_improvements_size = min(len(ls1_imp), len(ls2_imp), len(ls3_imp))
    draw_simple_plot(list(range(min_improvements_size)), 
        [ls1_imp[:min_improvements_size], ls2_imp[:min_improvements_size], ls3_imp[:min_improvements_size]], 
        ["mst initialization\nfull neighbourhood", "random initialization\nfull neighbourhood", "random initialization\nrandom part of neighbourhood"], 
        ["orange", "red", "black"], "repetition number", "impovements number", True,
        "Local Search improvements in {}".format(testcase), "plots/{}-ls-imp.png".format(testcase))
