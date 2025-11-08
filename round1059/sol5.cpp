#include <bits/stdc++.h>
using namespace std;

bool is_pal(const vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n/2; ++i)
        if (a[i] != a[n-1-i]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    if(!(cin >> t)) return 0;
    while (t--) {
        int n,k; cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        if (!is_pal(a)) {
            // already asymmetric -> append 1 repeated k times
            for (int i = 0; i < k; ++i) {
                if (i) cout << ' ';
                cout << 1;
            }
            cout << '\n';
        } else {
            // palindrome -> choose a value different from a[0] (and valid 1..n)
            int v = 1;
            if (v == a[0]) v = 2; // guaranteed n >= 3 so 2 is valid
            for (int i = 0; i < k; ++i) {
                if (i) cout << ' ';
                cout << v;
            }
            cout << '\n';
        }
    }
    return 0;
}
