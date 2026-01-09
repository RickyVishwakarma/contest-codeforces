#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> p;
        p.reserve(n);

        // append evens
        for (int i = 2; i <= n; i += 2) {
            p.push_back(i);
        }
        // append odds
        for (int i = 1; i <= n; i += 2) {
            p.push_back(i);
        }

        for (int x : p) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
