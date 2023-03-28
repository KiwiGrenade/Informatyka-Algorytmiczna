#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
int main(int argc, char** argv)
{
    std::ifstream graphDefinition;
    graphDefinition.open(argv[2], std::ios::out);
    if (graphDefinition.is_open())
    {
        Graph* graph = new Graph(graphDefinition);

        //serach the graph
        graph->BFS();
        if(*argv[1] == 'p')
        {
            graph->printSearchTree();
        }
    }
    else
    {
        std::cout << "Something went wrong. Could not open the file." << std::endl;
    }
    return 0;
}
