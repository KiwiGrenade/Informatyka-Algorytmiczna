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
    // number of nodes
    size_t n;
    // number of arcs
    size_t m;
//    std::vector <size_t> visited;
//    std::vector <size_t> finished;
//    std::vector <size_t> searchOrder;
    std::vector <std::vector<std::pair<size_t, size_t>>> adjacencyList;

//    void DFSVisit(size_t s) noexcept;
//    bool TPSVisit(size_t s, std::vector<size_t>& topOrder) noexcept;
//    void SCCVisit(size_t s, std::stack<size_t> &finVertices) noexcept;
//    void transpose() noexcept;
    void addEdge(size_t V1, size_t V2, size_t cost) noexcept;
public:

    explicit Graph(std::ifstream &graphDefinition) noexcept;
//    //zad 1
//    void BFS() noexcept;
//    void DFS() noexcept;
//    //zad 2
//    void TPS() noexcept;
//    //zad 3
//    void SCC() noexcept;
//    //zad 4
//    void GCP() noexcept;
//    void printSearchTree() noexcept;
//    void printSearchOrder() noexcept;
};



#endif //AOD_1_GRAPH_H
