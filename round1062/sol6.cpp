#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> adj(n+1);
        for (int i = 0; i < n-1; ++i) {
            int u, v; cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // iterative DFS to get parent and order
        vector<int> parent(n+1, 0);
        vector<int> order; order.reserve(n);
        parent[1] = 0;
        order.push_back(1);
        for (size_t i = 0; i < order.size(); ++i) {
            int v = order[i];
            for (int to : adj[v]) if (to != parent[v]) {
                parent[to] = v;
                order.push_back(to);
            }
        }

        // compute subtree sizes by iterating reversed order
        vector<int> sub(n+1, 1);
        for (int i = (int)order.size()-1; i >= 1; --i) { // skip root will be handled too but ok
            int v = order[i];
            int p = parent[v];
            if (p) sub[p] += sub[v];
        }

        ll ans = 0;
        for (int v = 1; v <= n; ++v) {
            int deg = (int)adj[v].size();
            if (deg - 1 >= k) {
                // v works for every root r
                ans += n;
            } else {
                // r == v always works (subtree size = n >= k since k <= n)
                ll cnt = 1;
                for (int u : adj[v]) {
                    int comp;
                    if (parent[u] == v) {
                        comp = sub[u];
                    } else {
                        // u is parent of v in our arbitrary rooting (or other side)
                        comp = n - sub[v];
                    }
                    if (comp <= n - k) cnt += comp;
                }
                ans += cnt;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
