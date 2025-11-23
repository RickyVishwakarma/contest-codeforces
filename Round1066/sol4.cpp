#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static ll solve_case(int n, ll L, ll R, const vector<ll>& a) {
    // We will try two variants:
    // 1) Force slope >= 0  → minimum happens at p = L
    // 2) Force slope <= 0  → minimum happens at p = R

    auto best_with = [&](ll P) {
        // t[i] = P - a[i]
        // s[i] ∈ {-1,0,1}
        // Unrestricted best is sum |t[i]| by taking s[i] = sign(t[i]).
        // Then we adjust slope condition by "fixing" some choices.
        ll unrestricted = 0;
        int cntPos = 0, cntNeg = 0, cntZero = 0;
        vector<ll> t(n);
        for (int i = 0; i < n; i++) {
            t[i] = P - a[i];
            unrestricted += abs(t[i]);
            if (t[i] > 0) cntPos++;
            else if (t[i] < 0) cntNeg++;
            else cntZero++;
        }

        // Initial slope = (#positive signs) - (#negative signs)
        int slope = cntPos - cntNeg;
        // For P = L, we want slope >= 0
        // For P = R, we want slope <= 0
        bool needNonNeg = (P == L);

        // If already valid, return this best
        if ((needNonNeg && slope >= 0) || (!needNonNeg && slope <= 0))
            return unrestricted;

        // We must fix slope by changing some s[i].
        int needFix = abs(slope);

        // Use zero elements first (cost 0 flips)
        int useFree = min(needFix, cntZero);
        needFix -= useFree;
        if (needFix == 0) return unrestricted;

        // Remaining adjustments cost something.
        vector<ll> repairCosts;
        // If P=L and slope<0 (needNonNeg case), we must increase slope:
        // That means turning negative t[i] from -1→0→+1 (each step cost |t[i]|).
        // If P=R and slope>0 (!needNonNeg case), we must decrease slope:
        // That means turning positive t[i] from +1→0→-1 similarly.

        if (needNonNeg) {
            // We need to move negatives up
            for (int i = 0; i < n; i++)
                if (t[i] < 0) {
                    ll c = abs(t[i]);
                    repairCosts.push_back(c);
                    repairCosts.push_back(c);
                }
        } else {
            // We need to move positives down
            for (int i = 0; i < n; i++)
                if (t[i] > 0) {
                    ll c = abs(t[i]);
                    repairCosts.push_back(c);
                    repairCosts.push_back(c);
                }
        }

        sort(repairCosts.begin(), repairCosts.end());
        ll penalty = 0;
        for (int i = 0; i < needFix; i++)
            penalty += repairCosts[i];

        return unrestricted - penalty;
    };

    ll resL = best_with(L);
    ll resR = best_with(R);
    return max({0LL, resL, resR});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        ll l, r;
        cin >> n >> l >> r;
        vector<ll> a(n);
        for (auto &x : a) cin >> x;
        cout << solve_case(n, l, r, a) << "\n";
    }
    return 0;
}
