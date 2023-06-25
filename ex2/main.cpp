#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <chrono>
#include "args.hpp"
class Graph {
public:
    Graph(size_t k, size_t i) {
        // neighbours list
        V2.resize(std::pow(2, k) * 2 + 2);  // +2 for source and sink

        std::random_device rd;
        std::mt19937 gen(rd());
        std::pair<size_t, size_t> range = {V2.size() / 2, V2.size() - 2};  // -2 to exclude source and sink

        for(size_t curr = 1; curr < V2.size() / 2; curr++) {  // Start from 1 to exclude source
            while(V2[curr].size() < i) {
                std::uniform_int_distribution<size_t> dis(range.first, range.second);
                size_t candidate = dis(gen);

                // if nodes aren't neighours
                if(std::find(V2[curr].begin(), V2[curr].end(), candidate) == V2[curr].end() &&
                   std::find(V2[candidate].begin(), V2[candidate].end(), curr) == V2[candidate].end()) {
                    // make them neighbours
                    V2[curr].push_back(candidate);
                    V2[candidate].push_back(curr);
                }
            }
            // Add edges from source to all vertices in V1
            V2[0].push_back(curr);  // source -> curr
            V2[curr].push_back(0);  // curr -> source
        }

        // Add edges from all vertices in V2 to sink
        for(size_t current = V2.size() / 2; current <= V2.size() - 2; current++) {
            V2[V2.size() - 1].push_back(current);  // sink -> current
            V2[current].push_back(V2.size() - 1);  // current -> sink
        }
    }

    int maxFlow() {
        int source = 0, sink = V2.size() - 1;  // Source and Sink

        // list of capa cities
        std::vector<std::vector<int>> capacities(V2.size(), std::vector<int>(V2.size(), 0));
        // list of parents
        std::vector<int> parent(V2.size());

        // set capacity of all edges to 1
        for(size_t i = 0; i < V2.size(); i++) {
            for(size_t j : V2[i]) {
                capacities[i][j] = 1;
            }
        }

        int new_flow;

        // retrun max flow
        int flow = 0;
        while((new_flow = bfs(source, sink, parent, capacities))) {
            flow += new_flow;
            int cur = sink;
            while(cur != source) {
                int prev = parent[cur];
                capacities[prev][cur] -= new_flow;
                capacities[cur][prev] += new_flow;
                cur = prev;
            }
        }

        return flow;
    }

private:
    std::vector<std::vector<size_t>> V2;

    int bfs(int source, int sink, std::vector<int>& parent, std::vector<std::vector<int>>& capacities) {
        // set list of parents to -1
        fill(parent.begin(), parent.end(), -1);
        // set the parent of source to -2
        parent[source] = -2;
        std::queue<std::pair<int, int>> q;
        q.push({source, std::numeric_limits<int>::max()});

        while (!q.empty()) {
            int cur = q.front().first;
            // flow from currnet
            int flow = q.front().second;
            q.pop();

            for (int next : V2[cur]) {
                // if next parent hasn't been
                if (parent[next] == -1 && capacities[cur][next] > 0) {
                    parent[next] = cur;
                    // set the current flow to minimum of flow and capacity of cur next
                    int new_flow = std::min(flow, capacities[cur][next]);
                    // next == sink -> terminate
                    if (next == sink)
                        return new_flow;

                    q.push({next, new_flow});
                }
            }
        }

        return 0;
    }

};
int main(int argc, char* argv[]) {
    // create output file
    auto args = cmdline_args(argc, argv);

    for(int k = 3; k <= args.size; k++) {
        std::cout << "k: " << k << std::endl;
        for(size_t i = 1; i <= k && i <= args.degree; i++) {
            Graph graph(k, i);
            auto maxFlow = graph.maxFlow();
            std::cout << "K: " << k << " " << "i: " << i << " " << "maxFlow: " << maxFlow << std::endl;
        }
    }
    return 0;
}
