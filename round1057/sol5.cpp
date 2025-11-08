#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

vector<int> sieve(int limit) {
    vector<char> is(limit + 1, true);
    vector<int> primes;
    is[0] = is[1] = false;
    for (int i = 2; i <= limit; ++i) {
        if (is[i]) {
            primes.push_back(i);
            if ((int64)i * i <= limit)
                for (int j = i * i; j <= limit; j += i)
                    is[j] = false;
        }
    }
    return primes;
}

inline int64 vp_fact(int64 x, int p) {
    int64 res = 0;
    while (x) {
        x /= p;
        res += x;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        auto primes = sieve(m);

        vector<int> best(n, INT_MAX);
        int64 ans = 0;

        for (int p : primes) {
            if (p > n) break;

            int64 vp_n = vp_fact(n, p);

            // For x = 1..n-1
            for (int64 x = p; x < n; x += p) {
                int64 vp_x = vp_fact(x, p);
                if (vp_x == vp_n) continue;
                int val = (int)min(vp_x, vp_n);
                if (val < best[x]) best[x] = val;
            }
        }

        for (int i = 1; i < n; ++i) {
            if (best[i] != INT_MAX) ans += best[i];
        }

        cout << ans << "\n";
    }

    return 0;
}
