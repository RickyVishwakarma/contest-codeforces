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
        vector<int> p(n), pos(n + 1);

        for (int i = 0; i < n; ++i) {
            cin >> p[i];
            pos[p[i]] = i; // 0-based position of value p[i]
        }

        // prefMin[k] = minimum position among labels 1..k
        vector<int> prefMin(n + 1);
        int curMin = n + 5;
        for (int k = 1; k <= n; ++k) {
            curMin = min(curMin, pos[k]);
            prefMin[k] = curMin;
        }

        // sufMax[k] = maximum position among labels k..n
        vector<int> sufMax(n + 2);
        int curMax = -1;
        for (int k = n; k >= 1; --k) {
            curMax = max(curMax, pos[k]);
            sufMax[k] = curMax;
        }

        bool ok = true;
        // Check cuts between {1..k} and {k+1..n}
        for (int k = 1; k <= n - 1; ++k) {
            // If all {1..k} appear after all {k+1..n}, no edge between them
            if (prefMin[k] > sufMax[k + 1]) {
                ok = false;
                break;
            }
        }

        cout << (ok ? "Yes\n" : "No\n");
    }

    return 0;
}
