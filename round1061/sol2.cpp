#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;

    while (t--) {
        int n, q;
        cin >> n >> q;
        string machines;
        cin >> machines;

        bool hasB = (machines.find('B') != string::npos);

        vector<long long> vals(q);
        for (auto &x : vals) cin >> x;

        for (long long x : vals) {
            if (!hasB) { // all A's
                cout << x << "\n";
                continue;
            }

            long long steps = 0;
            int i = 0;
            while (x > 0) {
                if (machines[i] == 'A') x -= 1;
                else x /= 2;
                steps++;
                i++;
                if (i == n) i = 0;
            }
            cout << steps << "\n";
        }
    }
    return 0;
}
