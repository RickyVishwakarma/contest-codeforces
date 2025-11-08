#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;

        long long g = a[0];
        for (int i = 1; i < n; i++)
            g = __gcd(g, a[i]);  

        long long ans = -1;
        for (long long x = 2; x <= 100; x++) { 
            if (__gcd(g, x) == 1) {  
                ans = x;
                break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
