#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;
int spf[MAXN + 5]; // smallest prime factor for sieve

// Build SPF sieve
void buildSieve() {
    for (int i = 2; i <= MAXN + 2; ++i) {
        if (!spf[i]) {
            for (int j = i; j <= MAXN + 2; j += i)
                if (!spf[j]) spf[j] = i;
        }
    }
}

// Extract unique prime factors of a number
vector<int> getFactors(int x) {
    vector<int> res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) x /= p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    buildSieve();

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;

        vector<int> a(n);
        vector<long long> b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        // --- Step 1: handle matching existing values directly ---
        unordered_map<int, long long> minCostForVal;
        minCostForVal.reserve(n * 2);

        for (int i = 0; i < n; ++i) {
            if (!minCostForVal.count(a[i]) || b[i] < minCostForVal[a[i]])
                minCostForVal[a[i]] = b[i];
        }

        vector<int> uniq;
        uniq.reserve(minCostForVal.size());
        for (auto &x : minCostForVal) uniq.push_back(x.first);
        sort(uniq.begin(), uniq.end());

        long long ans = LLONG_MAX;
        for (int i = 0; i + 1 < (int)uniq.size(); ++i) {
            long long cost = 1LL * (uniq[i + 1] - uniq[i]) * minCostForVal[uniq[i]];
            ans = min(ans, cost);
        }

        // --- Step 2: prime-based small adjustments ---
        unordered_map<int, vector<long long>> costMap;
        costMap.reserve(n * 3);

        for (int i = 0; i < n; ++i) {
            unordered_map<int, long long> local; // best cost per prime for this index

            for (int add = 0; add <= 2; ++add) {
                int val = a[i] + add;
                long long c = 1LL * add * b[i];
                vector<int> pf = getFactors(val);

                for (int p : pf) {
                    if (!local.count(p) || c < local[p])
                        local[p] = c;
                }
            }

            for (auto &kv : local)
                costMap[kv.first].push_back(kv.second);
        }

        for (auto it = costMap.begin(); it != costMap.end(); ++it) {
            vector<long long> &v = it->second;
            if (v.size() < 2) continue;
            nth_element(v.begin(), v.begin() + 1, v.end());
            ans = min(ans, v[0] + v[1]);
        }

        cout << ans << '\n';
    }
    return 0;
}
