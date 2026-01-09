#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--) {
        int n; 
        cin >> n;

        vector<long long> v(n);
        long long biggest = LLONG_MIN;

        for (int i = 0; i < n; ++i) {
            cin >> v[i];
            if (v[i] > biggest) biggest = v[i];
        }

        // compute sum of max of adjacent pairs on the ring
        long long costSum = 0;
        for (int i = 0; i < n; ++i) {
            int nxt = (i + 1 == n ? 0 : i + 1);
            costSum += (v[i] > v[nxt] ? v[i] : v[nxt]);
        }

        // final adjustment
        long long answer = costSum - biggest;
        cout << answer << '\n';
    }

    return 0;
}
