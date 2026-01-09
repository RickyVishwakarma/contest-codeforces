#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n;
        cin >> n;

        vector<int> floors(n);
        for (int i = 0; i < n; i++) {
            cin >> floors[i];
        }

        long long baseTime = 0;
        for (int i = 1; i < n; i++) {
            baseTime += llabs(floors[i] - floors[i - 1]);
        }

        long long best = baseTime;

        for (int idx = 0; idx < n; idx++) {
            long long current = baseTime;

            if (idx - 1 >= 0) {
                current -= llabs(floors[idx] - floors[idx - 1]);
            }
            if (idx + 1 < n) {
                current -= llabs(floors[idx] - floors[idx + 1]);
            }
            if (idx - 1 >= 0 && idx + 1 < n) {
                current += llabs(floors[idx - 1] - floors[idx + 1]);
            }

            best = min(best, current);
        }

        cout << best << '\n';
    }

    return 0;
}
