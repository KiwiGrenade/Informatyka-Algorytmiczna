//
// Created by jaskow on 21.03.23.
//

#ifndef AOD_1_GRAPH_H
#define AOD_1_GRAPH_H

#include <vector>
#include <list>
#include <stack>
#include <cstring>
#include <queue>
#include <limits>
class Graph
{
private:
    size_t maxWeight = 1;
    // adjacency list with weights
    std::list <std::pair<size_t, size_t>>* adjacencyList;
    std::vector<size_t> dijkstra(size_t source);
    std::vector<size_t> dial(size_t source);
    std::vector<size_t> radixheap(size_t source);
public:
    // number of nodes
    size_t n;
    // number of arcs
    size_t m;
    // min cost in gprah
    size_t minCost;
    // max cost in graph
    size_t maxCost;
    std::vector<size_t> getDistance(short alg, size_t V1) noexcept;
    void addEdge(size_t V1, size_t V2, size_t weight) noexcept;

    explicit Graph(std::ifstream &graphDefinition) noexcept;
};



#endif //AOD_1_GRAPH_H
