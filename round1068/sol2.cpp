#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    const int64 BIG = (int64)4e18;

    while (T--) {
        int n;
        cin >> n;

        vector<int64> R(n), B(n);
        for (auto &x : R) cin >> x;
        for (auto &x : B) cin >> x;

        // score form:  cur = sign * x + bias
        // but since initial score = 0, only bias matters.
        // keep ranges for both possible signs.
        struct Range { int64 low, high; };

        Range pos = {0, 0};       // reachable with + sign
        Range neg = {BIG, -BIG};  // unreachable at start

        for (int i = 0; i < n; i++) {
            Range nextPos = {BIG, -BIG};
            Range nextNeg = {BIG, -BIG};

            auto extend = [&](Range &dst, int64 l, int64 h) {
                dst.low = min(dst.low, l);
                dst.high = max(dst.high, h);
            };

            // transitions from (+) state
            if (pos.low <= pos.high) {
                // pick red → stays positive
                extend(nextPos,
                       pos.low - R[i],
                       pos.high - R[i]);

                // pick blue → flips to negative
                extend(nextNeg,
                       B[i] - pos.high,
                       B[i] - pos.low);
            }

            // transitions from (-) state
            if (neg.low <= neg.high) {
                // pick red → stays negative
                extend(nextNeg,
                       neg.low - R[i],
                       neg.high - R[i]);

                // pick blue → becomes positive
                extend(nextPos,
                       B[i] - neg.high,
                       B[i] - neg.low);
            }

            pos = nextPos;
            neg = nextNeg;
        }

        cout << max(pos.high, neg.high) << "\n";
    }
}
