#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    vector<vector<int>> adj(n+1);
    adj.reserve(n+1);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> dist(n+1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    // Every product from 1..k exists at least once (given). Initialize with 0.
    vector<int> ans(k+1, 0);
    for (int i = 1; i <= n; ++i) {
        // graph is connected so dist[i] should not be -1; guard just in case
        if (dist[i] >= 0) ans[a[i]] = max(ans[a[i]], dist[i]);
    }
    
    for (int type = 1; type <= k; ++type) {
        if (type > 1) cout << ' ';
        cout << ans[type];
    }
    cout << '\n';
    return 0;
}
