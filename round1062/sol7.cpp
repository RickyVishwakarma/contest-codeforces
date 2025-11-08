#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n), c(n);
        for (auto &x : a) cin >> x;
        for (auto &x : c) cin >> x;

        // Coordinate compression of a
        vector<ll> vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = vals.size();

        vector<ll> dp(m, INF), new_dp(m);

        // Initialize for first element
        for (int j = 0; j < m; ++j)
            dp[j] = (a[0] == vals[j] ? 0 : c[0]);

        // DP transitions
        for (int i = 1; i < n; ++i) {
            vector<ll> prefix(m);
            prefix[0] = dp[0];
            for (int j = 1; j < m; ++j)
                prefix[j] = min(prefix[j - 1], dp[j]);
            
            for (int j = 0; j < m; ++j) {
                ll cost = (a[i] == vals[j] ? 0 : c[i]);
                new_dp[j] = prefix[j] + cost;
            }
            dp.swap(new_dp);
        }

        cout << *min_element(dp.begin(), dp.end()) << "\n";
    }
}
