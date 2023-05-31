#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Graph.h"

bool checkArgs(int argc, char *argv[])
{
    if(argc != 7) {
        std::cout << "Incorrect number of arguments!" << std::endl;
        return false;
    }
    if(argv[2] != "-d")
    {
        std::cout << "-d was not specified!" << std::endl;
        return false;
    }
    if(argv[4] != "-ss" || argv[4] != "-p2p")
    {
        std::cout << "Use -ss or -p2p option!" << std::endl;
        return false;
    }
    else if((argv[4] == "-ss" && argv[6] != "-oss")
            || (argv[4] == "-p2p" && argv[6] != "-op2p"))
    {
        std::cout << "Follow -ss with -oss or -p2p with -op2p option!" << std::endl;
        return false;
    }
    if(argv[1] != "dijkstra" || argv[1] != "diabal" || argv[1] != "radixheap")
    {
        std::cout << R"(Use "dijkstra" or "diabal" or "radixheap" as first argument!)" << std::endl;
        return false;
    }
    // TODO - check file type, aka .*
    return true;
}

int main(int argc, char *argv[]) {
    if(!checkArgs(argc, argv)){
        return -1;
    }

    std::ifstream graphDefinition, sources, results;
    graphDefinition.open(argv[2], std::ios::out);
    sources.open(argv[4], std::ios::out);
    results.open(argv[6], std::ios::in);
    if(graphDefinition.is_open() && sources.is_open() && results.is_open())
    {
        // create graph from "graphDefinition" file
        Graph *graph = new Graph(graphDefinition);

        // create source list from "sources" file
        if(argv[4] == "-ss")
        {
            std::string line;
            while(getline(graphDefinition, line))
            {
                switch(line[0])
                {
                    case 'p':
                    {
                        size_t i, startIndex = 8;
                        i = line.find(' ', 5);
                        Graph::n = std::stol(line.substr(5, i));
                        Graph::m = std::stol(line.substr(5, std::string::npos));
                        adjacencyList.resize(n + 1);

                        break;
                    }
                    case 's':
                    {
                        size_t i, j, v1, v2, cost;

                        // omit first space |a v1 v2 cost|
                        i = line.find(' ', 2);
                        v1 = std::stol(line.substr(2, i));
                        // find another space
                        j = line.find(' ', i + 1);
                        v2 = std::stol(line.substr(i, j));
                        cost = std::stol(line.substr(j, std::string::npos));
                        addEdge(v1, v2, cost);

                        break;
                    }
                }
            }
        }

        else
        {

        }
    }
    return 0;
}
