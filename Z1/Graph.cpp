//
// Created by jaskow on 21.03.23.
//

#include <iostream>
#include "Graph.h"
#include "stack"
#include "fstream"
Graph::Graph(std::ifstream &graphDefinition) noexcept
{
    time = 0;
    std::string line;
    getline(graphDefinition, line);
    line == "D" ? isDirected = true : isDirected = false;
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

void Graph::BFS() noexcept
{
    visited.resize(n+1, false);
    searchOrder.clear();
    //mark the first vertex to access as visited

    //create a que of vertices yet to be fully marked
    std::list<size_t> queue;

    for(size_t i = 1; i <=n; i++)
    {
        if(!visited[i])
        {
            visited[i] = true;
            queue.push_back(i);
            while(!queue.empty())
            {
                //mark first vertex in queue
                size_t v = queue.front();
                searchOrder.push_back(v);
                queue.pop_front();

                //traverse all adjacent vertices of s
                for (size_t adjacent:adj[v])
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
        }
    }
}

bool Graph::DFSVisit(size_t s) noexcept
{
    visited[s] = true;
    searchOrder.push_back(s);

    for (size_t adjacent:adj[s])
    {
        if(!visited[adjacent])
        {
            DFSVisit(adjacent);
        }
    }

    return true;
}

bool Graph::DFS() noexcept
{
    visited.resize(n+1, false);
    searchOrder.clear();
    for (size_t i = 1; i <= m; i++)
    {
        if(!visited[i])
        {
            DFSVisit(i);
        }
    }
    return true;
}

bool Graph::TPS() noexcept
{
    if(!isDirected)
    {
        std::cout << "Error: Can't TPS an undirected graph!" << std::endl;
        return false;
    }
    visited.resize(n+1, false);
    finished.resize(n+1, false);
    time = 0;
    searchOrder.clear();
    std::vector<size_t> topOrder;

    for (size_t i = 1; i <= m; i++)
    {
        if(!visited[i])
        {
            if(!TPSVisit(i, topOrder))
            {
                std::cout << "There exists a directed cycle!" << std::endl;
                return false;
            }
        }
    }
    std::cout << "Graph is acyclic!" << std::endl;
    if(n <= 200)
    {
        for(size_t i = 0; i < n; i++)
        {
            std::cout << topOrder[i] << std::endl;
        }
    }

    return true;
}

bool Graph::TPSVisit(size_t s, std::vector<size_t>& topOrder) noexcept
{
    time++;

    visited[s] = time;
    searchOrder.push_back(s);

    for (size_t adjacent:adj[s])
    {
        if(!visited[adjacent])
        {
            TPSVisit(adjacent, topOrder);
        }
        else if(adjacent == s || ((finished[adjacent] > 0) && (finished[adjacent] < time+1)))
        {
            return false;
        }
    }
    time++;
    finished[s] = time;
    topOrder.push_back(s);
    return true;
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

