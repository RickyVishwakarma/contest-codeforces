#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        vector<int> cnt(n + 1, 0);
        for (int x : a) {
            if (x <= n) {
                cnt[x]++;
            }
        }
        int ans = 0;
        ans += cnt[0];
        for (int x = 1; x <= n; ++x) {
            if (cnt[x] == 0) continue;
            if (cnt[x] < x) {
                ans += cnt[x];
            } else {
                ans += cnt[x] - x;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
