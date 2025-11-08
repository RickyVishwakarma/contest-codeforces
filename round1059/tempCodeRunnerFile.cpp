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
        vector<int> p(n + 1), a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> p[i];
        int L, R;
        cin >> L >> R;

        // Construct modified array
        for (int i = 1; i <= n; ++i) {
            if (i >= L && i <= R) a[i] = p[i] + 1;
            else a[i] = p[i];
        }

        // Compute prefix sums
        vector<long long> pref_p(n + 1, 0), pref_a(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            pref_p[i] = pref_p[i - 1] + p[i];
            pref_a[i] = pref_a[i - 1] + a[i];
        }

        // Find l and r by checking where prefix differences change
        int l = -1, r = -1;
        for (int i = 1; i <= n; ++i) {
            long long diff_curr = pref_a[i] - pref_p[i];
            long long diff_prev = pref_a[i - 1] - pref_p[i - 1];
            if (diff_curr - diff_prev == 1) {
                if (l == -1) l = i;
                r = i;
            }
        }

        cout << "! " << l << " " << r << "\n";
    }

    return 0;
}
