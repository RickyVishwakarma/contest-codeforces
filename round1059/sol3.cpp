#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        unsigned long long a, b;
        cin >> a >> b;

        if (a == b) {
            cout << 0 << '\n';
            continue;
        }

        unsigned long long diff = a ^ b;

        // If one operation suffices
        if (diff <= a) {
            cout << 1 << '\n' << diff << '\n';
            continue;
        }

        // Compute bit-length of diff in a safe way (clzll undefined for 0)
        int bitlen = 0;
        if (diff > 0) bitlen = 64 - __builtin_clzll(diff);
        else bitlen = 0;

        // Construct mask = (1<<bitlen) - 1
        // Guard against bitlen == 64 (shift by 64 is UB), use all-ones
        unsigned long long mask;
        if (bitlen >= 64) mask = ~0ULL;
        else mask = (bitlen == 0 ? 0ULL : ((1ULL << bitlen) - 1ULL));

        // If mask is zero (shouldn't happen because diff>0), fallback to -1
        if (mask == 0) {
            cout << -1 << '\n';
            continue;
        }

        // Try using mask as first move (this is the sample-style approach)
        unsigned long long x1 = mask;
        unsigned long long a1 = a ^ x1;
        unsigned long long x2 = a1 ^ b;

        // Validate the dynamic constraints: x1 <= a (must hold) and x2 <= a1
        if (x1 <= a && x2 <= a1) {
            cout << 2 << '\n' << x1 << ' ' << x2 << '\n';
            continue;
        }

        // If that fails, try alternative: try smaller mask by reducing bitlen by 1 (fall back)
        bool ok = false;
        for (int reduce = 1; reduce <= 2 && !ok; ++reduce) {
            int bl = max(1, bitlen - reduce);
            unsigned long long m;
            if (bl >= 64) m = ~0ULL;
            else m = (1ULL << bl) - 1ULL;
            unsigned long long xx1 = m;
            unsigned long long aa1 = a ^ xx1;
            unsigned long long xx2 = aa1 ^ b;
            if (xx1 <= a && xx2 <= aa1) {
                cout << 2 << '\n' << xx1 << ' ' << xx2 << '\n';
                ok = true;
                break;
            }
        }
        if (ok) continue;

        // Final fallback: try the classic two-step split of diff (diff/2 and diff - diff/2)
        unsigned long long d1 = diff / 2;
        unsigned long long d2 = diff - d1;
        unsigned long long aa1 = a ^ d1;
        if (d1 <= a && d2 <= aa1) {
            cout << 2 << '\n' << d1 << ' ' << d2 << '\n';
            continue;
        }

        // If none of the constructive attempts worked, print -1
        cout << -1 << '\n';
    }
    return 0;
}
