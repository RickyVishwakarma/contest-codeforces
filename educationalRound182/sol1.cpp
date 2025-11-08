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
        vector<long long> a(n+1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        // prefix sums
        vector<long long> pref(n+1, 0);
        for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + a[i];
        long long S = pref[n];

        bool found = false;
        int L = 0, R = 0;

        for (int l = 1; l <= n-2 && !found; l++) {
            for (int r = l+1; r <= n-1; r++) {
                int s1 = pref[l] % 3;
                int s2 = (pref[r] - pref[l]) % 3;
                if (s2 < 0) s2 += 3;
                int s3 = (S - pref[r]) % 3;
                if (s3 < 0) s3 += 3;

                // either all same OR all different
                unordered_set<int> st = {s1, s2, s3};
                if (st.size() == 1 || st.size() == 3) {
                    L = l;
                    R = r;
                    found = true;
                    break;
                }
            }
        }

        if (found) cout << L << " " << R << "\n";
        else cout << "0 0\n";
    }
    return 0;
}
