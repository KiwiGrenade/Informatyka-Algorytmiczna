//
// Created by jaskow on 21.03.23.
//

#ifndef AOD_1_GRAPH_H
#define AOD_1_GRAPH_H

#include <vector>
#include <list>
#include <stack>
class Graph
{
private:
    bool isDirected;
    size_t n;
    size_t m;
    size_t time;
    std::vector <size_t> visited;
    std::vector <size_t> finished;
    std::vector <size_t> searchOrder;
    std::vector <std::vector<size_t>> adjacencyList;

    void DFSVisit(size_t s) noexcept;
    bool TPSVisit(size_t s, std::vector<size_t>& topOrder) noexcept;
    void SCCVisit(size_t s, std::stack<size_t> &finVertices) noexcept;

public:
    explicit Graph(std::ifstream &graphDefinition) noexcept;
    void addEdge(size_t V1, size_t V2) noexcept;
    void BFS() noexcept;
    void DFS() noexcept;
    bool TPS() noexcept;
    void SCC() noexcept;
    void GCP() noexcept;
    void transpose() noexcept;
    void printSearchOrder() noexcept;
};



#endif //AOD_1_GRAPH_H
