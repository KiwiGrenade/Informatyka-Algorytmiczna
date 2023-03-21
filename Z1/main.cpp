#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
int main(int argc, char** argv)
{
    std::ifstream testVector;
    testVector.open(argv[2], std::ios::out);
    if (testVector.is_open())
    {
        //get variables from file
        bool directed;
        size_t n, m;
        std::string line;
        getline(testVector, line);
        line == "D" ? directed = true : directed = false;
        getline(testVector, line);
        n = std::stol(line);
        getline(testVector, line);
        m = std::stol(line);

        //create the graph
        Graph *graph = new Graph(directed, n, m);
        while(getline(testVector, line))
        {
            size_t i, v1, v2;
            i = line.find(' ');
            v1 = std::stol(line.substr(0, i));
            v2 = std::stol(line.substr(i, std::string::npos));
            graph->addEdge(v1, v2);
        }

        //serach the graph
        graph->DFS(1);

        if(*argv[1] == 'p')
        {
            graph->print();
        }
    }
    else
    {
        std::cout << "Something went wrong. Could not open the file." << std::endl;
    }
    return 0;
}
