#include <bits/stdc++.h>
using namespace std;

bool isPossible(long long x, long long y, long long z) {
    for (int i = 0; i < 31; ++i) {
        int bx = (x >> i) & 1;
        int by = (y >> i) & 1;
        int bz = (z >> i) & 1;

        // Check if this bit combination is invalid
        bool valid = 
            (bx == 0 && by == 0 && bz == 0) ||
            (bx == 0 && by == 0 && bz == 1) ||
            (bx == 0 && by == 1 && bz == 0) ||
            (bx == 1 && by == 0 && bz == 0) ||
            (bx == 1 && by == 1 && bz == 1);

        if (!valid) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long x, y, z;
        cin >> x >> y >> z;
        cout << (isPossible(x, y, z) ? "YES\n" : "NO\n");
    }
    return 0;
}
