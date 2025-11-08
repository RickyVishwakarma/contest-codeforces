#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

struct DSU {
    vector<int> p, sz;
    DSU(int n) : p(n+1), sz(n+1,1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        return (p[x] == x ? x : p[x] = find(p[x]));
    }
    bool unite(int a, int b, int64 w, vector<pair<int64,int64>>& steps) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a,b);
        // join b into a
        p[b] = a;
        steps.push_back({w, (int64)sz[a] * sz[b]});
        sz[a] += sz[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        struct Edge {int u,v; int64 w;};
        vector<Edge> edges(n-1);
        for (int i=0;i<n-1;i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        // sort edges descending by weight
        sort(edges.begin(), edges.end(), [](auto &a, auto &b){
            return a.w > b.w;
        });

        DSU dsu(n);
        vector<pair<int64,int64>> steps; 
        // (edgeWeight, how many new pairs gained)

        for (auto &e : edges) {
            dsu.unite(e.u, e.v, e.w, steps);
        }

        // now build prefix sums
        // steps[i] = (weight, pairs)
        // each pair contributes "weight" to cost when threshold is <= weight
        vector<int64> X, Y; 
        // X = possible f([x]) thresholds
        // Y = minimal sum of vertex weights

        int64 cur = 0;
        for (auto &p : steps) {
            cur += p.second * p.first;
            X.push_back(p.first);
            Y.push_back(cur);
        }

        int q; cin >> q;
        while (q--) {
            int64 t; cin >> t;
            // find smallest weight >= t
            int idx = lower_bound(X.begin(), X.end(), t, greater<int64>()) - X.begin();
            if (idx == (int)X.size()) {
                // smaller than all weights → put t on one vertex
                cout << t << "\n";
            } else {
                // sum so far + (remaining pairs)*t
                int64 ans = Y[idx] - (X[idx] - t) * (steps[idx].second);
                cout << ans << "\n";
            }
        }
    }
}
