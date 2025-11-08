#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        // build prefix max
        vector<int> pref(n);
        pref[0] = a[0];
        for (int i = 1; i < n; i++)
            pref[i] = max(pref[i - 1], a[i]);

        unordered_map<int, long long> dp, next_dp;
        dp[a[0]] = 0;
        dp[pref[0]] = 0;

        for (int i = 1; i < n; i++) {
            next_dp.clear();
            bool need_less = ((i - 1) % 2 == 0); // if prev index (i-1) is odd (1-based), need < relation

            for (auto it = dp.begin(); it != dp.end(); ++it) {
                int prev_val = it->first;
                long long cost = it->second;

                if (need_less) {
                    // need prev < current
                    if (pref[i] > prev_val) {
                        if (!next_dp.count(pref[i]) || cost < next_dp[pref[i]])
                            next_dp[pref[i]] = cost;
                    } else {
                        int new_prev = pref[i] - 1;
                        if (new_prev >= 0) {
                            long long extra = max(0LL, prev_val - new_prev);
                            if (!next_dp.count(pref[i]) || cost + extra < next_dp[pref[i]])
                                next_dp[pref[i]] = cost + extra;
                        }
                    }
                } else {
                    // need prev > current
                    int limit = prev_val - 1;
                    if (limit < 0) continue;

                    if (pref[i] <= limit) {
                        if (!next_dp.count(pref[i]) || cost < next_dp[pref[i]])
                            next_dp[pref[i]] = cost;
                    }

                    int target = min(limit, a[i]);
                    if (target >= 0) {
                        long long dec_cost = min(a[i] - target, pref[i] - target);
                        if (!next_dp.count(target) || cost + dec_cost < next_dp[target])
                            next_dp[target] = cost + dec_cost;
                    }
                }
            }

            // small optimization: keep few best
            if (next_dp.size() > 8) {
                vector<pair<int, long long>> items(next_dp.begin(), next_dp.end());
                sort(items.begin(), items.end(), [](const pair<int,long long> &x, const pair<int,long long> &y) {
                    return x.second < y.second;
                });
                next_dp.clear();
                for (int j = 0; j < (int)std::min<size_t>(6, items.size()); j++)
                    next_dp[items[j].first] = items[j].second;
            }

            dp.swap(next_dp);
        }

        long long answer = LLONG_MAX;
        for (auto it = dp.begin(); it != dp.end(); ++it)
            answer = min(answer, it->second);

        cout << answer << "\n";
    }
    return 0;
}
