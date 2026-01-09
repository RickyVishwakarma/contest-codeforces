#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        for (int i = 0 ; i < n ; i++) cin >> a[i];

        sort(a.begin(), a.end());

        ll mn = a[0];
        ll diff = a[1] - a[0];

        cout << max(mn, diff) << '\n';
    }
    return 0;
}
