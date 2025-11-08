#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pair<int, int>> intervals(m);
        vector<int> cover(n + 2, 0);

        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            intervals[i] = {l, r};
            cover[l]++;
            cover[r + 1]--;
        }

        // prefix sum to get coverage count
        for (int i = 1; i <= n; ++i)
            cover[i] += cover[i - 1];

        // find least covered position
        int pos0 = 1;
        for (int i = 2; i <= n; i++) {
            if (cover[i] < cover[pos0]) pos0 = i;
        }

        // build permutation
        vector<int> p(n);
        int cur = 1;
        for (int i = 1; i <= n; ++i) {
            if (i == pos0) p[i - 1] = 0;
            else p[i - 1] = cur++;
        }

        for (int i = 0; i < n; ++i)
            cout << p[i] << (i + 1 == n ? '\n' : ' ');
    }
}
