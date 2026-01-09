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
        ll x, y;
        cin >> n >> x >> y;

        string s;
        cin >> s;

        vector<ll> p(n);
        for (int i = 0; i < n; i++) cin >> p[i];

        ll minA = 0, minB = 0;
        ll maxA = 0, maxB = 0;

        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                ll a_min = (p[i] + 1) / 2;
                ll b_min = p[i] - a_min;

                minA += a_min;
                minB += b_min;

                maxA += p[i];
                maxB += p[i] - 1;
            } else {
                ll b_min = (p[i] + 1) / 2;
                ll a_min = p[i] - b_min;

                minA += a_min;
                minB += b_min;

                maxA += (p[i] - 1) / 2;
                maxB += p[i];
            }
        }

        if (minA <= x && x <= maxA && minB <= y && y <= maxB) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
