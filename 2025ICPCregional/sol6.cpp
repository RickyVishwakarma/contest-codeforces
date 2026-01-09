#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v;
    int w;
    bool operator<(Edge const& o) const {
        return w < o.w;
    }
};

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) {
        p.resize(n + 1);
        r.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) ++r[a];
        return true;
    }
};

// small, fast gcd (works for positive ints)
inline int G(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#if defined(__GNUC__) && !defined(__clang__)
    // nothing
#endif

    int n;
    if (!(cin >> n)) return 0;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i];

    // Collect candidate edges: for each r, for each distinct gcd g of some subarray [l..r], add edge (l, r) with weight g.
    vector<Edge> edges;
    edges.reserve(n * 40);

    // prev: list of pairs (gcd_value, leftmost_index) for subarrays ending at previous position
    vector<pair<int,int>> prev;

    for (int r = 1; r <= n; ++r) {
        vector<pair<int,int>> cur;
        // start with single element [r,r]
        cur.emplace_back(p[r], r);

        // extend previous segments by p[r], merge equal gcds keeping earliest left index
        for (auto &pr : prev) {
            int g = G(pr.first, p[r]);
            if (cur.back().first == g) {
                // same gcd value — keep earliest left index
                cur.back().second = min(cur.back().second, pr.second);
            } else {
                cur.emplace_back(g, pr.second);
            }
        }

        // For each distinct gcd segment ending at r, we can add edge from its leftmost start to r.
        // Note: we add only segments with l < r (non-trivial), because self-loops are useless.
        for (auto &pr : cur) {
            int g = pr.first;
            int l = pr.second;
            if (l < r) edges.push_back({l, r, g});
        }

        prev.swap(cur);
    }

    // If there are not enough edges (rare), we can also add all adjacent edges (i, i+1) as fallback:
    // (usually edges already include them, but ensure connectivity)
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i+1, G(p[i], p[i+1])});
    }

    sort(edges.begin(), edges.end());

    DSU dsu(n);
    ll total = 0;
    int used = 0;
    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total += e.w;
            ++used;
            if (used == n - 1) break;
        }
    }

    cout << total << '\n';
    return 0;
}
