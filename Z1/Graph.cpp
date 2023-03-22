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
    getline(graphDefinition, line);
    line == "D" ? directed = true : directed = false;
    getline(graphDefinition, line);
    n = std::stol(line);
    getline(graphDefinition, line);
    m = std::stol(line);


    visited.resize(n+1, false);
    //make space for the last element
    adj.resize(n+1);
    //create the graph
    while(getline(graphDefinition, line))
    {
        size_t i, v1, v2;
        i = line.find(' ');
        v1 = std::stol(line.substr(0, i));
        v2 = std::stol(line.substr(i, std::string::npos));
        addEdge(v1, v2);
    }
}

void Graph::addEdge(size_t V1, size_t V2) noexcept
{
    //add vertex V2 to list of vertices adjacent to V1
    adj[V1].push_back(V2);
}

void Graph::BFS(size_t s) noexcept
{
    //mark the first vertex to access as visited
    visited[s] = true;

    //create a que of vertices yet to be fully marked
    std::list<size_t> queue;
    //add s as the first vertex to mark
    queue.push_back(s);

    while(!queue.empty())
    {
        //mark first vertex in queue
        s = queue.front();
        searchOrder.push_back(s);
        queue.pop_front();

        //traverse all adjacent vertices of s
        for (size_t adjacent:adj[s])
        {
            //if vertex hasn't been visited
            if(!visited[adjacent])
            {
                //visit it and queue to be marked (and printed)
                visited[adjacent] = true;
                queue.push_back(adjacent);
            }
        }
    }
    visited.resize(n, false);
}

void Graph::DFS(size_t s) noexcept
{
    visited[s] = true;
    searchOrder.push_back(s);

    for (size_t adjacent:adj[s])
    {
        if(!visited[adjacent])
        {
            DFS(adjacent);
        }
    }
}

void Graph::printSearchOrder() noexcept
{
    for (size_t vertice:searchOrder)
    {
        std::cout << vertice << " ";
    }
}

void Graph::printGraph() noexcept
{
    //generate graph tree (BFS OR DFS)
}
