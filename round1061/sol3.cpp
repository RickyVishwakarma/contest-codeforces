#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        vector<int> cnt(n + 1, 0);
        for (int x : a) cnt[x]++;

        vector<int> divCnt(n + 1, 0);
        // count how many numbers are divisible by each possible divisor
        for (int d = 1; d <= n; ++d) {
            for (int j = d; j <= n; j += d)
                divCnt[d] += cnt[j];
        }

        int ans = 1;
        for (int g = n; g >= 1; --g) {
            if (divCnt[g] >= n - k) {
                ans = g;
                break;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
