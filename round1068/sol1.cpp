#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        vector<int> mark(n);
        int lockUntil = -1;  
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                lockUntil = max(lockUntil, i + k);
            }
            if (i <= lockUntil) {
                mark[i] = 1;
            }
        }
        int canSleep = 0;
        for (int i = 0; i < n; i++) {
            if (!mark[i]) canSleep++;
        }
        cout << canSleep << "\n";
    }
    return 0;
}
