#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 250000 + 5;

int n;
vector<pair<int,ll>> g[MAXN];
int sz[MAXN];
vector<ll> contrib;

int dfs(int u, int p) {
    sz[u] = 1;
    for (auto edge : g[u]) {
        int v = edge.first;
        ll w = edge.second;
        if (v == p) continue;
        int sub = dfs(v,u);
        sz[u] += sub;
        int smaller = min(sub, n - sub);
        // Each edge contributes "w" repeated smaller times
        for (int i = 0; i < smaller; i++) {
            contrib.push_back(w);
        }
    }
    return sz[u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        for (int i=1;i<=n;i++) g[i].clear();
        contrib.clear();

        for (int i=0;i<n-1;i++) {
            int u,v;
            ll w;
            cin >> u >> v >> w;
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }

        dfs(1,-1);

        sort(contrib.rbegin(), contrib.rend());
        vector<ll> pref(contrib.size()+1, 0);
        for (int i=0;i<(int)contrib.size();i++) {
            pref[i+1] = pref[i] + contrib[i];
        }

        int q;
        cin >> q;
        while(q--) {
            ll t;
            cin >> t;
            int k = lower_bound(pref.begin(), pref.end(), t) - pref.begin();
            cout << k + t << "\n";
        }
    }
}
