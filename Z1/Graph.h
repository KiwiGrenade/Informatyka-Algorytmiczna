//
// Created by jaskow on 21.03.23.
//

#ifndef AOD_1_GRAPH_H
#define AOD_1_GRAPH_H

#include <vector>
#include <list>
class Graph
{
private:
    bool directed;
    size_t n;
    size_t m;
    std::vector <bool> visited;
    std::vector <size_t> searchOrder;
    std::vector <std::list<size_t>> adj;

public:
    explicit Graph(std::ifstream &graphDefinition) noexcept;
    void addEdge(size_t V1, size_t V2) noexcept;
    void BFS(size_t s) noexcept;
    void DFS(size_t s) noexcept;
    void printSearchOrder() noexcept;
    void printGraph() noexcept;
};



#endif //AOD_1_GRAPH_H
