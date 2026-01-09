#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;

// custom gcd (no std::gcd needed)
ll mygcd(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a >= 0 ? a : -a;
}

// Check feasibility for candidate d
bool feasible(ld d, const vector<ll> &r, ll k, int n, int L) {
    int i = 1;
    vector<int> leaders;
    while (i <= n) {
        if (i > L) return false;  // must be leader
        leaders.push_back(i);
        ld limit = (ld)r[i] - d;
        int j = i + 1;
        while (j <= n && (ld)r[j] <= limit + 1e-15L) j++;
        i = j;
    }

    if ((int)leaders.size() > L) return false;

    if (leaders.size() == 1) return true;

    ld span = 0;
    for (int t = 0; t + 1 < (int)leaders.size(); t++) {
        int a = leaders[t], b = leaders[t+1];
        span += (ld)r[a] + (ld)r[b] + d;
    }
    return span <= (ld)k + 1e-12L;
}

// rational approximation
pair<ll,ll> find_fraction(ld x) {
    ll bestA = 0, bestB = 1;
    ld bestErr = fabsl(x);

    const ll LIMIT = 1000000;
    for (ll b = 1; b <= LIMIT; b++) {
        ll a = llround(x * (ld)b);
        ld err = fabsl(x - (ld)a/(ld)b);
        if (err < bestErr) {
            bestErr = err;
            bestA = a;
            bestB = b;
        }
    }
    ll g = mygcd(bestA, bestB);
    return {bestA/g, bestB/g};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll k;
    int n, L;
    cin >> k >> n >> L;
    vector<ll> r(n+1);
    for (int i = 1; i <= n; i++) cin >> r[i];

    // check if d = 0 works
    if (!feasible(0.0L, r, k, n, L)) {
        cout << 0 << "\n";
        return 0;
    }

    // binary search on d
    ld lo = 0, hi = 2e18;
    for (int it = 0; it < 120; it++) {
        ld mid = (lo + hi) * 0.5;
        if (feasible(mid, r, k, n, L)) lo = mid;
        else hi = mid;
    }

    ld best = lo;
    ld nearInt = floor(best + 0.5);

    if (fabsl(best - nearInt) < 1e-12L) {
        cout << (ll)nearInt << "\n";
        return 0;
    }

    auto frac = find_fraction(best);
    cout << frac.first << "/" << frac.second << "\n";
}
