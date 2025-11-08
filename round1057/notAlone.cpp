#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)9e18;

ll tile_line_cost(const vector<ll> &b) {
    int L = (int)b.size();
    if (L == 0) return 0;
    vector<ll> dp(L+1, INF);
    dp[0] = 0;
    for (int i = 0; i < L; ++i) {
        if (dp[i] >= INF) continue;
        // tile of size 2: i, i+1
        if (i + 2 <= L) {
            ll c = llabs(b[i] - b[i+1]);
            dp[i+2] = min(dp[i+2], dp[i] + c);
        }
        // tile of size 3: i, i+1, i+2
        if (i + 3 <= L) {
            ll mn = min(b[i], min(b[i+1], b[i+2]));
            ll mx = max(b[i], max(b[i+1], b[i+2]));
            ll c = mx - mn;
            dp[i+3] = min(dp[i+3], dp[i] + c);
        }
    }
    return dp[L];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        ll ans = INF;

        // Case 1: no wrap (linear tiling of all n elements)
        ans = min(ans, tile_line_cost(a));

        // Case 2: wrap pair (n-1,0) -> remove indices n-1 and 0, solve on [1..n-2]
        if (n - 2 >= 0) {
            ll wrap = llabs(a[n-1] - a[0]);
            vector<ll> seg;
            for (int i = 1; i <= n-2; ++i) seg.push_back(a[i]);
            ll inner = tile_line_cost(seg);
            if (inner < INF) ans = min(ans, wrap + inner);
        }

        // Case 3: wrap triple (n-1,0,1) -> remove n-1,0,1; solve on [2..n-2]
        if (n - 3 >= 0) {
            ll mn = min(a[n-1], min(a[0], a[1]));
            ll mx = max(a[n-1], max(a[0], a[1]));
            ll wrap = mx - mn;
            vector<ll> seg;
            for (int i = 2; i <= n-2; ++i) seg.push_back(a[i]);
            ll inner = tile_line_cost(seg);
            if (inner < INF) ans = min(ans, wrap + inner);
        }

        // Case 4: wrap triple (n-2,n-1,0) -> remove n-2,n-1,0; solve on [1..n-3]
        if (n - 3 >= 0) {
            ll mn = min(a[n-2], min(a[n-1], a[0]));
            ll mx = max(a[n-2], max(a[n-1], a[0]));
            ll wrap = mx - mn;
            vector<ll> seg;
            for (int i = 1; i <= n-3; ++i) seg.push_back(a[i]);
            ll inner = tile_line_cost(seg);
            if (inner < INF) ans = min(ans, wrap + inner);
        }

        cout << ans << '\n';
    }
    return 0;
}
