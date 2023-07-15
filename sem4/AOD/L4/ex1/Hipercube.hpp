#pragma once
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <bitset>
#include <random>
#include <optional>
#include <deque>
#include <cassert>
#include <queue>

inline size_t HWeight(size_t num)
{
    // cast int to bits
    auto bits = std::bitset<32>(num);
    // return number of ones
    return bits.count();
}

// generate edge capacity
inline size_t genCap(size_t l)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(1, std::pow(2, l));

    return dis(gen);
}

class Hipercube {
public:
    // create hipercube graph - k (hipercube level)
    Hipercube(size_t k, bool print) : k(k), print(print) {
        n = std::pow(2,k);

        for(size_t i = 0; i < n; i++) {
            auto fi = std::unordered_map<size_t, size_t>{};
            // c(i)
            auto ci = std::unordered_map<size_t, size_t>{};

            for(size_t j = 0; j < k; j++) {

                size_t key = static_cast<size_t>(std::pow(2.0, static_cast<double>(j))) ^ i;
                fi[key] = 0;

                // e(j) > e(i) -> assign capacity to A(i, j)
                if(key > i) {
                    // calculate l
                    size_t l = std::max(HWeight(key), k - HWeight(key));
                    l = std::max(l, HWeight(i));
                    l = std::max(l, k - HWeight(i));

                    size_t capacity = genCap(l);
                    ci[key] = capacity;
                }

                else {
                    ci[key] = 0;
                }
            }
            f.push_back(fi);
            c.push_back(ci);
        }
    }

    std::optional<std::vector<size_t>> findPath(){
        size_t t = n - 1;
        std::deque<size_t> stack = {};
        // list of parents
        std::vector<size_t> pre = {};
        std::vector<bool> visited = {};
        stack.push_back(0);

        // setAll(pre, maximum), setAll(visited,false)
        for(size_t i = 0; i < n; i++) {
            pre.push_back(INF);
            visited.push_back(false);
        }

        // visit index 0
        visited[0] = true;

        // stack isn't empty and pre[t] = max
        while(!stack.empty() && pre[t] == INF) {
            assert(!stack.empty());
            // get node from the top of the stack
            size_t first = stack.front();
            stack.pop_front();
            size_t u = first;
            // iterate through all neighbours of u
            for(size_t i = 0; i < k; i++) {
                size_t v = static_cast<size_t>(std::pow(2, i)) ^ u;
                // node isn't visited capacity(u, v) > flow(u, v)
                if(!visited[v] && c[u][v] > f[u][v]) {
                    visited[v] = true;
                    stack.push_back(v);
                    pre[v] = u;
                }
            }
        }

        // no path from source to destination found
        if(pre[t] == INF) {
            return std::nullopt;
        }

        // recreate the path from source to t
        std::vector<size_t> path = {t};
        size_t x = t;
        while(x != 0) {
            path.push_back(pre[x]);
            x = pre[x];
        }

        return path;
    }

    std::pair<size_t, size_t> Karp() {
        size_t nPaths = 0;

        // set flow to 0
        for(size_t i = 0; i < n; i++) {
            for(size_t j = 0; j < k; j++) {
                size_t key = static_cast<size_t>(std::pow(2,j)) ^ i;
                f[i][key] = 0;
            }
        }

        // while there exists a path in residual graph
        auto optionalPath = findPath();
        while (optionalPath.has_value()) {
            std::vector<size_t> path = *optionalPath;
            nPaths++;

            // find minimum capacity
            auto minCap = INF;
            for(size_t i = 0; i < path.size() - 1; i++) {
                size_t u = path[i + 1];
                size_t v = path[i];
                minCap = std::min(minCap, c[u][v] - f[u][v]);
            }

            // add minimum capacity to each edge in the path
            for(size_t i = 0; i < path.size() - 1; i++) {
                size_t u = path[i + 1];
                size_t v = path[i];
                f[u][v] += minCap;
                f[v][u] -= minCap;
            }

            optionalPath = findPath();
        }

        size_t max_flow = 0;
        for(auto i = 0; i < k; i++) {
            auto v = std::pow(2, i);
            max_flow += f[0][v];
        }
        if(print) {
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < k; j++) {
                    size_t key = static_cast<unsigned int>(std::pow(2, j)) ^ i;
                    if(key > i) {
                        std::cout << "x[" << i << "]" << "[" << key << "] = " << f[i][key] << std::endl;
                    }
                }
            }
        }
        return {max_flow, nPaths};
    }

private:
    static constexpr size_t INF = std::numeric_limits<size_t>::max();
    bool print;

public:
    size_t k;
    size_t n;
    std::vector<std::unordered_map<size_t, size_t>> f;
    std::vector<std::unordered_map<size_t, size_t>> c;
};
