#include <algorithm>
#include <queue>
#include <limits>
#include <utility>
#include <vector>

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using namespace std;
using ll = long long;

struct Dinic {
    int n;
    vector<vector<pair<int, int>>> g; // (node, index)
    vector<ll> cap;

    Dinic(int n) : n(n), g(n) {}

    vector<int> calculate_levels(int source) {
        vector<int> level(n, -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);

        while (!q.empty()) {
            const int u = q.front();
            q.pop();

            for (auto [v, i] : g[u]) {
                if (cap[i] == 0 || level[v] != -1) continue;

                level[v] = level[u] + 1;
                q.push(v);
            } 
        }

        return level;
    }
    
    void add_dir_edge(int u, int v, ll c) {
        g[u].emplace_back(v, sz(cap));
        cap.push_back(c);
        g[v].emplace_back(u, sz(cap));
        cap.push_back(0);
    }

    void add_undir_edge(int u, int v, ll c) {
        g[u].emplace_back(v, sz(cap));
        cap.push_back(c);
        g[v].emplace_back(u, sz(cap));
        cap.push_back(c);
    }

    ll push_flow(int source, int sink, vector<int>& level, vector<int>& it) {

        auto dfs = [&](auto&& self, int u, ll f) -> ll {
            if (u == sink) return f;

            ll tf = 0;
            for (int &k = it[u]; k < sz(g[u]); ++k) {
                auto [v, i] = g[u][k];
                if (cap[i] == 0 || level[v] != level[u] + 1) continue;

                ll r = self(self, v, min(f - tf, cap[i]));
                if (r > 0) {
                    cap[i] -= r;
                    cap[i ^ 1] += r;
                    tf += r;
                }

                if (tf == f) return tf; // do not advance k
            }
            return tf;
        };

        return dfs(dfs, source, numeric_limits<ll>::max());
    }

    // O(n^2 m), or O(sqrt(n) m) if unit capacities.
    ll run(int source, int sink) {
        if (source == sink) return -1;


        ll flow = 0;
        ll add;

        while (true) {
            auto level = calculate_levels(source);
            if (level[sink] == -1) break;

            vector<int> it(n, 0);

            while ((add = push_flow(source, sink, level, it)) > 0) flow += add;
        }

        return flow;
    }
};
