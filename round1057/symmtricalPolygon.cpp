#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        sort(a.begin(), a.end());
        unordered_map<ll, int> freq;
        for (ll len : a) freq[len]++;

        vector<ll> pairs;
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            ll len = it->first;
            int cnt = it->second;
            int numPairs = cnt / 2;
            for (int i = 0; i < numPairs; ++i)
                pairs.push_back(len);
        }

        if (pairs.empty()) {
            cout << 0 << "\n";
            continue;
        }

        sort(pairs.begin(), pairs.end());
        ll sumPairs = accumulate(pairs.begin(), pairs.end(), 0LL);
        ll totalPerimeter = 2 * sumPairs;
        ll largest = pairs.back();

        ll ans = 0;

        // Even symmetrical polygon (all mirrored pairs)
        if (totalPerimeter - 2 * largest > 0)
            ans = max(ans, totalPerimeter);

        // Odd symmetrical polygon (with one middle side)
        for (auto it = freq.begin(); it != freq.end(); ++it) {
            ll mid = it->first;
            int cnt = it->second;
            if (cnt % 2 == 1) {
                ll peri = totalPerimeter + mid;
                ll biggest = max(largest, mid);
                if (peri - biggest > biggest)
                    ans = max(ans, peri);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
