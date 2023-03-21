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
    std::vector <std::list<size_t>> adj;
    std::vector <bool> visited;

public:
    Graph(bool directed, size_t n, size_t m) noexcept;
    void addEdge(size_t V1, size_t V2) noexcept;
    void BFS(size_t s) noexcept;
    void DFS(size_t s) noexcept;
    void print() noexcept;
};



#endif //AOD_1_GRAPH_H
