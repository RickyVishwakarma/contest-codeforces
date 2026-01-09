#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<long long> a(n);
        unordered_map<long long, int> cnt;
        cnt.reserve(n * 2);

        for (auto &x : a) {
            cin >> x;
            cnt[x]++;
        }

        // Step 1: Collect all distinct values up to max(a)
        vector<long long> vals;
        vals.reserve(cnt.size());
        for (auto &p : cnt)
            vals.push_back(p.first);
        sort(vals.begin(), vals.end());

        long long maxA = vals.back();

        // Step 2: Determine which numbers are valid
        unordered_map<long long, bool> valid;
        valid.reserve(vals.size());

        for (long long x : vals) {
            bool ok = true;
            for (long long mult = x; mult <= k; mult += x) {
                if (!cnt.count(mult)) { ok = false; break; }
            }
            if (ok) valid[x] = true;
        }

        // Step 3: Check feasibility — each ai must have a valid divisor
        bool possible = true;
        for (auto &x : a) {
            bool has = false;
            for (long long d = 1; 1LL * d * d <= x; d++) {
                if (x % d == 0) {
                    if (valid.count(d)) has = true;
                    long long d2 = x / d;
                    if (valid.count(d2)) has = true;
                }
                if (has) break;
            }
            if (!has) { possible = false; break; }
        }

        if (!possible) {
            cout << -1 << "\n";
            continue;
        }

        // Step 4: Build minimal B
        vector<long long> B;
        for (long long x : vals) {
            if (!valid.count(x)) continue;

            bool keep = true;
            for (long long d = 1; 1LL * d * d <= x; d++) {
                if (x % d == 0) {
                    if (d < x && valid.count(d)) { keep = false; break; }
                    long long d2 = x / d;
                    if (d2 < x && valid.count(d2)) { keep = false; break; }
                }
            }
            if (keep) B.push_back(x);
        }

        // Output
        cout << B.size() << "\n";
        for (auto x : B) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
