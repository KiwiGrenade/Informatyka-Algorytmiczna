//
// Created by jaskow on 21.03.23.
//

#include <iostream>
#include "Graph.h"
#include "stack"
#include "fstream"
Graph::Graph(std::ifstream &graphDefinition) noexcept
{
    std::string line;
    // create the graph from graphDefinition file
    while(getline(graphDefinition, line))
    {
        switch(line[0])
        {
            case 'p':
            {
                size_t i;

                i = line.find(' ', 5);
                Graph::n = std::stol(line.substr(5, i));
                Graph::m = std::stol(line.substr(5, std::string::npos));
                adjacencyList.resize(n + 1);

                break;
            }
            case 'a':
            {
                size_t i, j, v1, v2, cost;

                // omit first space |a v1 v2 cost|
                i = line.find(' ', 2);
                v1 = std::stol(line.substr(2, i));
                // find another space
                j = line.find(' ', i + 1);
                v2 = std::stol(line.substr(i, j));
                cost = std::stol(line.substr(j, std::string::npos));
                addEdge(v1, v2, cost);

                break;
            }
        }
    }
}
//
void Graph::addEdge(size_t V1, size_t V2, size_t cost) noexcept
{
    //add vertex V2 with it's cost to list of vertices adjacent to V1
    Graph::adjacencyList[V1].push_back(std::pair(V2, cost));
}
//
//void Graph::BFS() noexcept
//{
//    visited.clear();
//    visited.resize(n+1, false);
//    searchOrder.clear();
//    //mark the first vertex to access as visited
//
//    //create a que of vertices yet to be fully marked
//    std::list<size_t> queue;
//
//    for(size_t i = 1; i <=n; i++)
//    {
//        if(!visited[i])
//        {
//            visited[i] = true;
//            queue.push_back(i);
//            while(!queue.empty())
//            {
//                //mark first vertex in queue
//                size_t v = queue.front();
//                searchOrder.push_back(v);
//                queue.pop_front();
//
//                //traverse all adjacent vertices of s
//                for (size_t adjacent:adjacencyList[v])
//                {
//                    //if vertex hasn't been visited
//                    if(!visited[adjacent])
//                    {
//                        //visit it and queue to be marked (and printed)
//                        visited[adjacent] = true;
//                        queue.push_back(adjacent);
//                    }
//                }
//            }
//        }
//    }
//}
//
//void Graph::DFS() noexcept
//{
//    visited.clear();
//    visited.resize(n+1, false);
//    searchOrder.clear();
//
//    for (size_t i = 1; i <= n; i++)
//    {
//        if(!visited[i])
//        {
//            DFSVisit(i);
//        }
//    }
//}
//
//void Graph::DFSVisit(size_t s) noexcept
//{
//    visited[s] = true;
//    searchOrder.push_back(s);
//
//    for (size_t adjacent:adjacencyList[s])
//    {
//        if(!visited[adjacent])
//        {
//            DFSVisit(adjacent);
//        }
//    }
//}
//
//
//void Graph::TPS() noexcept
//{
//    if(!isDirected)
//    {
//        std::cout << "Error: Can't TPS an undirected graph!" << std::endl;
//    }
//    visited.clear();
//    visited.resize(n+1, false);
//    finished.clear();
//    finished.resize(n+1, false);
//    time = 0;
//    searchOrder.clear();
//
//    std::vector<size_t> topOrder;
//
//    //search the vertex if unvisited
//    for (size_t i = 1; i <= n; i++)
//    {
//        if(!visited[i])
//        {
//            if(!TPSVisit(i, topOrder))
//            {
//                std::cout << "There exists a directed cycle!" << std::endl;
//                return;
//            }
//        }
//    }
//    std::cout << "Graph is acyclic!" << std::endl;
//    if(n <= 200)
//    {
//        for(size_t i = 0; i < n; i++)
//        {
//            std::cout << topOrder[i] << " ";
//        }
//        std::cout << std::endl;
//    }
//}
//
//bool Graph::TPSVisit(size_t s, std::vector<size_t>& topOrder) noexcept
//{
//    time++;
//
//    visited[s] = time;
//    searchOrder.push_back(s);
//
//    for (size_t adjacent:adjacencyList[s])
//    {
//        if(!visited[adjacent])
//        {
//            TPSVisit(adjacent, topOrder);
//        }
////        else if(adjacent == s || ((finished[adjacent] > 0) && (finished[adjacent] > time+1)))
//        else if(finished[adjacent] == 0)
//        {
//            return false;
//        }
//    }
//    time++;
//    finished[s] = time;
//    topOrder.push_back(s);
//    return true;
//}
//
//
//void Graph::SCC() noexcept
//{
//    std::vector<std::vector<size_t>> sccList;
//    std::stack <size_t> finVertices;
//
//    visited.clear();
//    visited.resize(n+1, false);
//    searchOrder.clear();
//
//
//    if(!isDirected)
//    {
//        std::cout << "Error: Graph is undirected!" << std::endl;
//        return;
//    }
//    for(size_t i = 1; i <= n; i++)
//    {
//        if(!visited[i])
//        {
//            SCCVisit(i, finVertices);
//        }
//    }
//
//    transpose();
//
//    visited.clear();
//    visited.resize(n+1, false);
//    searchOrder.clear();
//
//    if(n <= 200)
//    {
//        std::cout << "Strongly connected components:" << std::endl;
//    }
//
//    while(!finVertices.empty())
//    {
//        if(!visited[finVertices.top()])
//        {
//            searchOrder.clear();
//            DFSVisit(finVertices.top());
//            if(n <= 200)
//            {
//                printSearchOrder();
//            }
//            sccList.push_back(searchOrder);
//        }
//        finVertices.pop();
//    }
//    std::cout << "Number of SCC: " << sccList.size() << std::endl;
//    std::cout << "Numbers of vertices in SCCs:" << std::endl;
//    for(const std::vector<size_t>& i : sccList)
//    {
//        std::cout << i.size() << std::endl;
//    }
//}
//
//void Graph::SCCVisit(size_t s, std::stack<size_t> &finVertices) noexcept
//{
//    visited[s] = true;
//    searchOrder.push_back(s);
//    for (size_t adjacent:adjacencyList[s])
//    {
//        if(!visited[adjacent])
//        {
//            SCCVisit(adjacent, finVertices);
//        }
//    }
//    finVertices.push(s);
//}
//
//void Graph::printSearchOrder() noexcept
//{
//    std::cout << "Search order: " << std::endl;
//    for (size_t vertex:searchOrder)
//    {
//        std::cout << vertex << std::endl;
//    }
//}
//
//void Graph::GCP() noexcept
//{
//    std::vector<int> color;
//    color.resize(n+1, 0);
//    std::list<size_t> queue(n+1);
//
//    for(size_t i = 1; i <= n; i++)
//    {
//        if(color[i] == 0)
//        {
//            color[i] = 1;
//            queue.push_back(i);
//            while(!queue.empty())
//            {
//                //mark first vertex in queue
//                size_t v = queue.front();
//                queue.pop_front();
//
//                size_t nRed = 0;
//                size_t nGreen = 0;
//                //traverse all adjacent vertices of s
//                for (size_t adjacent:adjacencyList[v])
//                {
//                    //if vertex hasn't been visited
//                    if(color[adjacent] == color[v])
//                    {
//                        std::cout << "Graph can't be 2-colored!" << std::endl;
//                        return;
//                    }
//                    else if(color[adjacent] == 0)
//                    {
//                        color[adjacent] = -color[v];
//                        queue.push_back(adjacent);
//                    }
//                }
//            }
//        }
//    }
//    std::cout << "Graph can be 2-colored!" << std::endl;
//    if(n <= 200)
//    {
//        std::cout << "Red vertices:" << std::endl;
//        for(int i = 1; i <= n; i++)
//        {
//            if(color[i] == 1)
//            {
//                std::cout << i << " ";
//            }
//        }
//        std::cout << std::endl << "Green vertices:" << std::endl;
//        for(int i = 1; i <= n; i++)
//        {
//            if(color[i] == -1)
//            {
//                std::cout << i << " ";
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//
//void Graph::transpose() noexcept
//{
//    std::vector<std::vector<size_t>> T;
//    T.resize(n + 1);
//    for (size_t i = 0 ;i < n + 1; i++)
//    {
//        for(size_t j : adjacencyList[i])
//        {
//            T[j].push_back(i);
//        }
//    }
//    adjacencyList = T;
//}
//
//void Graph::printSearchTree() noexcept
//{
//    if(n > 200)
//    {
//        return;
//    }
//    std::cout << "Tree:" << std::endl;
//    for (size_t i = 1; i <= n; i++ )
//    {
//        std::cout << i << " --> ";
//        for(size_t v : adjacencyList[i])
//        {
//            std::cout << v << " ";
//        }
//        std::cout << std::endl;
//    }
//}

