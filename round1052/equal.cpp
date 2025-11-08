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
        vector<int> a(n);              // <-- you must give size n
        for (int i = 0; i < n; i++) cin >> a[i];

        unordered_map<int, int> mp;    // frequency map
        for (int i = 0; i < n; i++) {
            mp[a[i]]++;
        }

        int ans = 0;
        // try every possible frequency k
        for (int k = 1; k <= n; k++) {
            int cnt = 0;
            for (auto &p : mp) {
                if (p.second >= k) cnt++;
            }
            ans = max(ans, cnt * k);
        }

        cout << ans << "\n";
    }
    return 0;
}
