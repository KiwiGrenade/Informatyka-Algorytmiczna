#include <iostream>
#include <chrono>
#include <fstream>
#include "Hipercube.hpp"
#include "args.hpp"

int main(int argc, char* argv[])
{
    // check arguments
    cmdline_args args(argc, argv);

    // create output file
    std::ofstream output = std::ofstream("karp.csv");
    output << "k,time,max-flow,paths" << std::endl;

    size_t tries = 1;

    for(int k = 1; k <= args.size; k++) {
        std::cout << "k: " << k << std::endl;
        size_t avgMaxFlow{};
        size_t avgNumPaths{};
        Hipercube hipercube(k, args.printFlow);

        // start timer
        auto start = std::chrono::high_resolution_clock::now();

        for(size_t t = 0; t < tries; t++) {
            Hipercube hipercubeCopy = hipercube;
            auto[max_flow, num_paths] = hipercubeCopy.Karp();
            avgMaxFlow += max_flow;
            avgNumPaths += num_paths;
        }

        // stop timer
        auto end = std::chrono::high_resolution_clock::now();
        // calculate time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // write to file
        output << k << ",edmonds-karp," << duration << "," << avgMaxFlow / tries << "," << avgNumPaths / tries << std::endl;
        // print flow


         std::cerr << "Execution time: " << duration << " ms" << std::endl;
         std::cerr << "Number of paths: " << avgNumPaths << std::endl;
    }

    return 0;
}
