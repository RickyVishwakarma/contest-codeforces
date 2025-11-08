#include <bits/stdc++.h>
using namespace std;

long long solve_case() {
    int n, m;
    cin >> n >> m;

    vector<int> fav(m);
    for (int &x : fav) cin >> x;

    vector<int> segmentEnds;
    int tail = fav[0];

    for (int i = 1; i < m; ++i) {
        if (fav[i] == fav[i - 1] + 1) {
            tail = fav[i];
        } else {
            segmentEnds.push_back(tail);
            tail = fav[i];
        }
    }
    segmentEnds.push_back(tail);


    if (segmentEnds.size() == 1) {
        long long res = max(0LL, 1LL * n - segmentEnds[0] + 1);
        return res;
    }


    long long k0 = segmentEnds[0];
    for (int j = 1; j + 1 < (int)segmentEnds.size(); ++j) {
        if (1LL * segmentEnds[j] - j != k0)
            return 0;  
    }

    if (k0 < 1 || k0 > n) return 0;
    long long lastBlock = k0 + (int)segmentEnds.size() - 1;

    return (segmentEnds.back() <= lastBlock ? 1 : 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cout << solve_case() << '\n';
    }
    return 0;
}
