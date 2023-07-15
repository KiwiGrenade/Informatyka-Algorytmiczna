#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
int main(int argc, char** argv)
{
    std::ifstream graphDefinition;
    graphDefinition.open(argv[1], std::ios::out);
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
                graph->printSearchOrder();
                break;
            }
            case '2':
            {
                graph->DFS();
                graph->printSearchOrder();
                break;
            }
            //zad 2
            case '3':
            {
                graph->TPS();
                break;
            }
            //zad 3
            case '4':
            {
                graph->SCC();
                break;
            }
            //zad 4
            case '5':
            {
                graph->GCP();
                break;
            }
            default:
            {
                std::cout << "Wrong algorithm argument!" << std::endl;
                break;
            }
        }
        if(*argv[3] == 'p')
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
