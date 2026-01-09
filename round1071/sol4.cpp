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
        int N = 1 << n;

        vector<int> used(N, 0);
        vector<int> ans;

        // Process bits from high to low
        for (int b = n - 1; b >= 0; b--) {
            for (int x = N - 1; x >= 0; x--) {
                if (!used[x] && ((x >> b) & 1)) {
                    used[x] = 1;
                    ans.push_back(x);
                }
            }
        }

        // Append remaining number (only 0)
        for (int x = 0; x < N; x++) {
            if (!used[x]) ans.push_back(x);
        }

        for (int x : ans) cout << x << " ";
        cout << "\n";
    }
    return 0;
}
