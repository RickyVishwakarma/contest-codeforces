#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string r;
        cin >> r;
        int n = r.size();

        // Required assertion
        for (char c : r) {
            assert(c == 's' || c == 'u');
        }

        vector<int> pos;
        for (int i = 0; i < n; i++) {
            if (r[i] == 's') pos.push_back(i);
        }

        int cntS = pos.size();
        int ans = 0;

        // Case 1: No 's'
        if (cntS == 0) {
            if (n % 2 == 1) cout << (n + 1) / 2 << "\n";
            else cout << (n + 2) / 2 << "\n";
            continue;
        }

        // Case 2: Only one 's'
        if (cntS == 1) {
            ans++; // need one more 's'
        }

        // Prefix u's
        ans += pos[0];

        // Suffix u's
        ans += (n - 1 - pos.back());

        // Gaps between s
        for (int i = 0; i + 1 < cntS; i++) {
            int len = pos[i + 1] - pos[i] - 1;
            if (len > 0) {
                if (len % 2 == 0) ans += len;
                else ans += len - 1;
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
