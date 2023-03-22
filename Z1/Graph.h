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
    bool isDirected;
    bool isDAG;
    size_t n;
    size_t m;
    size_t time;
    std::vector <size_t> visited;
    std::vector <size_t> finished;
    std::vector <size_t> searchOrder;
    std::vector <std::list<size_t>> adj;

    bool DFSVisit(size_t s) noexcept;
    bool TPSVisit(size_t s, std::vector<size_t>& topOrder) noexcept;

public:
    explicit Graph(std::ifstream &graphDefinition) noexcept;
    void addEdge(size_t V1, size_t V2) noexcept;
    void BFS() noexcept;
    bool DFS() noexcept;
    bool TPS() noexcept;
    void printSearchOrder() noexcept;
    void printGraph() noexcept;

};



#endif //AOD_1_GRAPH_H
