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
        switch (*argv[2])
        {
            //zad 1
            case '1':
            {
                graph->BFS();
            }
            case '2':
            {
                graph->DFS();
            }
            //zad 2
            case '3':
            {
                graph->TPS();
            }
            //zad 3
            case '4':
            {
                graph->SCC();
            }
            //zad 4
            case '5':
            {
                graph->GCP();
            }
        }
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
