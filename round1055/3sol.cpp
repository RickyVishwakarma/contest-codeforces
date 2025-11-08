#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> arr(n+1);
        for (int i = 1; i <= n; i++) cin >> arr[i];

        // prefix sums for zeros/ones
        vector<int> prefZero(n+1,0), prefOne(n+1,0), prefEq(n+1,0);

        for (int i = 1; i <= n; i++) {
            prefZero[i] = prefZero[i-1] + (arr[i]==0);
            prefOne[i]  = prefOne[i-1]  + (arr[i]==1);
            if (i > 1) prefEq[i] = prefEq[i-1] + (arr[i]==arr[i-1]);
            else prefEq[i] = 0;
        }

        while (q--) {
            int L, R;
            cin >> L >> R;
            int len = R-L+1;

            int zeros = prefZero[R] - prefZero[L-1];
            int ones  = prefOne[R]  - prefOne[L-1];

            if (zeros % 3 != 0 || ones % 3 != 0) {
                cout << -1 << "\n";
                continue;
            }

            int moves = zeros/3 + ones/3;

            // check if this segment is strictly alternating (no equal neighbors)
            bool alt = (prefEq[R] - prefEq[L] == 0);

            if (alt && len % 6 == 0) moves++;

            cout << moves << "\n";
        }
    }
    return 0;
}
