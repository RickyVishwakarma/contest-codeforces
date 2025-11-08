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
        for (int i = 0; i < n; ++i) cin >> a[i];

        sort(a.begin(), a.end());

        int ans = 1;
        for (int d = 1; d <= n; ++d) {
            int cnt = 0;
            for (int x : a) {
                if (x % d == 0 || x >= 2 * d)
                    cnt++;
            }
            if (cnt >= n - k)
                ans = d;
        }

        cout << ans << "\n";
    }

    return 0;
}
