#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        int neg = 0, zero = 0;
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (x == -1) ++neg;
            else if (x == 0) ++zero;
        }
        int ans = zero + (neg % 2) * 2; 
        cout << ans << '\n';
    }
    return 0;
}
