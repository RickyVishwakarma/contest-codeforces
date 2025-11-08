#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 676767677LL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if(!(cin >> t)) return 0;
    while(t--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // c[i] = a[i] - n + i  (0-based i)
        vector<ll> c(n);
        for (int i = 0; i < n; ++i) c[i] = a[i] - n + i;

        // differences must be in {0,1,2}
        vector<ll> d;
        bool ok = true;
        for (int i = 0; i + 1 < n; ++i) {
            ll diff = c[i+1] - c[i];
            if (!(diff == 0 || diff == 1 || diff == 2)) { ok = false; break; }
            d.push_back(diff);
        }
        if (!ok) { cout << 0 << '\n'; continue; }

        ll ways = 0;
        for (int start = 0; start <= 1; ++start) {
            vector<int> x(n, -1);
            x[0] = start;
            bool valid = true;
            for (int i = 0; i + 1 < n; ++i) {
                ll nxt = d[i] - x[i];
                if (nxt != 0 && nxt != 1) { valid = false; break; }
                x[i+1] = (int)nxt;
            }
            if (!valid) continue;

            // compute L (should be total number of left-wearers)
            ll L = (ll)x[0] - c[0];
            if (L < 0 || L > n) continue;

            // consistency check using c formula, and compute sum(x)
            ll prefix = 0; // sum_{j < i} x[j]
            for (int i = 0; i < n; ++i) {
                ll Li = 2*prefix + x[i] - c[i];
                if (Li != L) { valid = false; break; }
                prefix += x[i];
            }
            if (!valid) continue;

            // IMPORTANT: ensure L equals actual number of left-wearers (sum of x)
            if (prefix != L) continue;

            ways++;
        }

        cout << (ways % MOD) << '\n';
    }
    return 0;
}
