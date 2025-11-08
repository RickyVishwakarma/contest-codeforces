#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> parent, order;
int n;

void dfs(int v, int p) {
    parent[v] = p;
    order.push_back(v);
    for (int u : adj[v]) {
        if (u == p) continue;
        dfs(u, v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        adj.assign(n + 1, {});
        parent.assign(n + 1, -1);
        order.clear();

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs(1, -1);

        vector<pair<int, int>> ops; // (type, node)
        for (int i = 1; i < (int)order.size(); i++) {
            int u = order[i];
            ops.push_back(make_pair(2, parent[u]));
            ops.push_back(make_pair(1, 0));
        }

        if (!ops.empty() && ops.back().first == 2)
            ops.push_back(make_pair(1, 0));

        cout << ops.size() << "\n";
        for (size_t i = 0; i < ops.size(); i++) {
            int type = ops[i].first;
            int node = ops[i].second;
            if (type == 1)
                cout << 1 << "\n";
            else
                cout << 2 << " " << node << "\n";
        }
    }

    return 0;
}
