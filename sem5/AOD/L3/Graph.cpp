//
// Created by jaskow on 21.03.23.
//

#include <iostream>
#include "Graph.h"
#include "stack"
#include "fstream"
Graph::Graph(std::ifstream &graphDefinition) noexcept
{
    minCost = std::numeric_limits<size_t>::max();
    maxCost = 0;
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
                n = std::stol(line.substr(5, i));
                m = std::stol(line.substr(5, std::string::npos));
                adjacencyList = new std::list<std::pair<size_t, size_t>>[n+1];
                break;
            }
            case 'a':
            {
                size_t i, j, v1, v2, cost;
                if(cost < minCost)
                {
                    minCost = cost;
                }
                if(cost > maxCost)
                {
                    maxCost = cost;
                }
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
void Graph::addEdge(size_t V1, size_t V2, size_t weight) noexcept
{
    adjacencyList[V1].push_back(std::make_pair(V2, weight));
    // add vertex V2 with it's cost to list of vertices adjacent to V1
}

std::vector<size_t> Graph::getDistance(short alg, size_t V1) noexcept {
    std::vector<size_t> result;
    switch(alg)
    {
        case 0:
        {
            result = dijkstra(V1);
            break;
        }
        case 1:
        {
            result = dial(V1);
            break;
        }
        default:
        {
            std::cout << "Wrong algorithm!" << std::endl;
        }
    }
    return result;
}

std::vector<size_t> Graph::dijkstra(size_t source)
{
    // priority queue with access to smallest element
    std::priority_queue<
            std::pair<size_t, size_t>,
            std::vector<std::pair<size_t, size_t>>,
            std::greater<>
    > priorityQueue;

    std::vector<size_t> distanceList(n, std::numeric_limits<size_t>::max());

    // initialize priorityQueue and distance with 0
    priorityQueue.emplace(0, source);
    distanceList[source] = 0;


    while (priorityQueue.empty() == false){

        // get tops weight
        size_t u = priorityQueue.top().second;
        // pop top
        priorityQueue.pop();

        std::list<std::pair<size_t, size_t>>::iterator i;
        for (i = adjacencyList[u].begin(); i != adjacencyList[u].end(); ++i) {
            // Get vertex label and weight of current
            // adjacent of u.
            size_t v = (*i).first;
            size_t weight = (*i).second;

            // If there is shorted path to v through u.
            if (distanceList[v] > distanceList[u] + weight) {
                // Updating distanceList of v
                distanceList[v] = distanceList[u] + weight;
                priorityQueue.emplace(distanceList[v], v);
            }
        }
    }
    return distanceList;
}

std::vector<size_t> Graph::dial(size_t source)
{
    std::cout << source << std::endl;
    std::vector<std::pair<size_t, std::list<size_t>::iterator>> distance(n);

    for (size_t i = 0; i < n; i++) {
        distance[i].first = std::numeric_limits<size_t>::max();
    }

    distance[source].first = 0;

    // buckets number = max arc cost
    std::vector<std::list<size_t>> buckets(maxCost);
    buckets[0].push_back(source);
    long unsigned long idx = 0;

    while(true) {
        // find first empty bucket
        while(!buckets[idx].empty()  && idx < buckets.size())
        {
            idx++;
        }
        if(idx == buckets.size())
        {
            break;
        }

        // take top vertex and pop it
        size_t u = buckets[idx].front();
        buckets[idx].pop_front();

        // process all neigbours of u and update if required
        for(auto i = adjacencyList[u].begin(); i != adjacencyList[u].end(); ++i){
            size_t v = (*i).first;
            size_t vWeight = (*i).second;

            size_t du = distance[u].first;
            size_t dv = distance[v].first;

            // if there is a shorter path to v thtough u
            if(dv > du + vWeight)
            {
                // if dv != INF it must be in bucket[dv]
                if (dv != std::numeric_limits<size_t>::max()) {
                    buckets[dv].erase(distance[v].second);
                }

                // update the distance
                distance[v].first = du + vWeight;
                dv = distance[v].first;

                // if the distance is greater than the bucket size, resize the bucket
                if(dv > buckets.size()){
                    buckets.resize(dv + maxWeight * 2);
                }
                // push v into proper bucket
                buckets[dv].push_front(v);
                // update the v's distance
                distance[v].second = buckets[dv].begin();
            }
        }
    }

    std::vector<size_t> d(n);
    for(size_t i = 0; i < n; ++i){
        d[i] = distance[i].first;
    }
    return d;
}