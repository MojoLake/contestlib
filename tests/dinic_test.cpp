#include "test.hpp"

#include <algorithm>
#include <limits>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

#include "../graph/dinic.cpp"

using Edge = std::tuple<int, int, long long>;

long long edmonds_karp(int n, const std::vector<Edge>& edges, int source,
                      int sink) {
    std::vector<std::vector<long long>> capacity(n,
                                                 std::vector<long long>(n));
    for (auto [u, v, c] : edges) capacity[u][v] += c;

    long long flow = 0;
    while (true) {
        std::vector<int> parent(n, -1);
        parent[source] = source;
        std::queue<int> queue;
        queue.push(source);

        while (!queue.empty() && parent[sink] == -1) {
            int u = queue.front();
            queue.pop();
            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && capacity[u][v] > 0) {
                    parent[v] = u;
                    queue.push(v);
                }
            }
        }
        if (parent[sink] == -1) return flow;

        long long add = std::numeric_limits<long long>::max();
        for (int v = sink; v != source; v = parent[v])
            add = std::min(add, capacity[parent[v]][v]);
        for (int v = sink; v != source; v = parent[v]) {
            capacity[parent[v]][v] -= add;
            capacity[v][parent[v]] += add;
        }
        flow += add;
    }
}

long long run_dinic(int n, const std::vector<Edge>& edges) {
    Dinic dinic(n);
    for (auto [u, v, c] : edges) dinic.add_dir_edge(u, v, c);
    return dinic.run(0, n - 1);
}

int main() {
    EXPECT_EQ(run_dinic(4, {{0, 1, 3}, {1, 3, 2}, {0, 2, 4},
                            {2, 3, 5}, {3, 0, 3}}),
              6LL);
    EXPECT_EQ(run_dinic(3, {{0, 1, 5}}), 0LL);
    EXPECT_EQ(run_dinic(2, {{0, 1, 3}, {0, 1, 7}}), 10LL);
    EXPECT_EQ(run_dinic(2, {{0, 1, 4'000'000'000LL}}), 4'000'000'000LL);

    Dinic undirected(3);
    undirected.add_undir_edge(0, 1, 4);
    undirected.add_undir_edge(1, 2, 3);
    EXPECT_EQ(undirected.run(0, 2), 3LL);

    std::mt19937 rng(0xC0FFEE);
    for (int iteration = 0; iteration < 300; ++iteration) {
        const int n = 2 + static_cast<int>(rng() % 7);
        std::vector<Edge> edges;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u != v && rng() % 4 == 0)
                    edges.emplace_back(u, v, 1 + rng() % 20);
            }
        }
        EXPECT_EQ(run_dinic(n, edges), edmonds_karp(n, edges, 0, n - 1));
    }

    if (test::failures == 0) std::cout << "dinic: all tests passed\n";
    return test::failures == 0 ? 0 : 1;
}
