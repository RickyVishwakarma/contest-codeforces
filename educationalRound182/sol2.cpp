#include <bits/stdc++.h>
using namespace std;

int computeCost(const vector<int>& p) {
    int n = (int)p.size()-1;
    int L = -1, R = -1;
    for (int i = 1; i <= n; i++) {
        if (p[i] != i) {
            if (L == -1) L = i;
            R = i;
        }
    }
    if (L == -1) return 0;
    return R - L + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> p(n+1);
        vector<bool> used(n+1,false);
        vector<int> zeros;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i] == 0) zeros.push_back(i);
            else used[p[i]] = true;
        }

        if (zeros.empty()) {
            cout << computeCost(p) << "\n";
            continue;
        }

        if (zeros.size() == 1) {
            int pos = zeros[0];
            int missing = -1;
            for (int x = 1; x <= n; x++) if (!used[x]) missing = x;
            p[pos] = missing;
            cout << computeCost(p) << "\n";
            continue;
        }

        int L = zeros.front();
        int R = zeros.back();
        cout << R - L + 1 << "\n";
    }
}
