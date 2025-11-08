#include <bits/stdc++.h>
using namespace std;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n+1), b(n+1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        vector<vector<int>> dp(n+1, vector<int>(2, 0));
        dp[1][0] = 1;  // no swap
        dp[1][1] = 1;  // swap

        for (int i = 2; i <= n; i++) {
            for (int prev = 0; prev < 2; prev++) {
                for (int cur = 0; cur < 2; cur++) {
                    int aPrev = (prev == 0 ? a[i-1] : b[i-1]);
                    int bPrev = (prev == 0 ? b[i-1] : a[i-1]);
                    int aCur  = (cur == 0 ? a[i]   : b[i]);
                    int bCur  = (cur == 0 ? b[i]   : a[i]);

                    if (aPrev <= aCur && bPrev <= bCur) {
                        dp[i][cur] = (dp[i][cur] + dp[i-1][prev]) % MOD;
                    }
                }
            }
        }

        int ans = (dp[n][0] + dp[n][1]) % MOD;
        cout << ans << "\n";
    }
    return 0;
}


