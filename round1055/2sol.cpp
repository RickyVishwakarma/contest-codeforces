#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canCatch(ll n, ll kr, ll kc, ll dr, ll dc, ll steps) {
    ll lowR = max(0LL, kr - steps);
    ll highR = min(n, kr + steps);
    ll lowC = max(0LL, kc - steps);
    ll highC = min(n, kc + steps);
    ll rowGap = max(abs(dr - lowR), abs(dr - highR));
    ll colGap = max(abs(dc - lowC), abs(dc - highC));

    return (rowGap <= steps && colGap <= steps);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        ll n, rk, ck, rd, cd;
        cin >> n >> rk >> ck >> rd >> cd;
        ll left = 0, right = n, answer = n;
        while (left <= right) {
            ll mid = (left + right) / 2;
            if (canCatch(n, rk, ck, rd, cd, mid)) {
                answer = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        cout << answer << "\n";
    }
    return 0;
}
