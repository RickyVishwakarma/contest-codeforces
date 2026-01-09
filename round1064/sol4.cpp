#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> cnt(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            cnt[x]++;
        }

        vector<int> f;
        f.reserve(n);
        for (int i = 1; i <= n; i++)
            if (cnt[i] > 0) f.push_back(cnt[i]);

        sort(f.begin(), f.end(), greater<int>());
        f.push_back(0);

        long long ans = 1;
        for (int i = 0; i + 1 < (int)f.size(); i++) {
            int gap = f[i] - f[i + 1];
            ans = (ans * (gap + 1)) % MOD;
        }

        cout << ans % MOD << "\n";
    }

    return 0;
}
