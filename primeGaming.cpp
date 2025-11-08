#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static int memoVis[1 << 20];
static unsigned char memoRes[1 << 20]; // store 1 or 2
int stamp = 1;
int NMAX = 20;

int nGlob;
vector<vector<int>> allowedByR; // allowed positions for each r
int valMaskGlob; // bits set where pile value == 2

// remove k-th one (1-based k) from mask (bits 0..n-1), return new mask
inline int removeKthOne(int mask, int k, int n) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
            ++cnt;
            if (cnt == k) {
                return mask & ~(1 << i);
            }
        }
    }
    return mask; // should not happen
}

// compute result (1 or 2) for given mask; turn is determined from n and popcount(mask)
unsigned char solveMask(int mask) {
    if (memoVis[mask] == stamp) return memoRes[mask];
    int r = __builtin_popcount((unsigned)mask);
    if (r == 1) {
        // only one pile left -> return its value (1 or 2)
        int idx = __builtin_ctz((unsigned)mask); // position of only set bit
        unsigned char res = ((valMaskGlob >> idx) & 1) ? 2 : 1;
        memoVis[mask] = stamp;
        memoRes[mask] = res;
        return res;
    }

    bool aliceTurn = (((nGlob - r) & 1) == 0); // true -> Alice, false -> Bob
    unsigned char res;
    if (aliceTurn) {
        // Alice: OR over children -> can short-circuit on 2
        res = 1;
        for (int g : allowedByR[r]) {
            int child = removeKthOne(mask, g, nGlob);
            unsigned char cRes = solveMask(child);
            if (cRes == 2) { res = 2; break; }
        }
    } else {
        // Bob: AND over children -> can short-circuit on 1
        res = 2;
        for (int g : allowedByR[r]) {
            int child = removeKthOne(mask, g, nGlob);
            unsigned char cRes = solveMask(child);
            if (cRes == 1) { res = 1; break; }
        }
    }

    memoVis[mask] = stamp;
    memoRes[mask] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    const ll MOD = 1000000007LL;

    while (T--) {
        int m, k;
        cin >> nGlob >> m;
        cin >> k;
        vector<int> good(k);
        for (int i = 0; i < k; ++i) cin >> good[i];

        // precompute allowed moves for each current pile-count r (1..n)
        allowedByR.assign(nGlob + 1, vector<int>());
        for (int r = 1; r <= nGlob; ++r) {
            for (int g : good) if (g <= r) allowedByR[r].push_back(g);
        }

        ll totalConfigs = 1;
        for (int i = 0; i < nGlob; ++i) totalConfigs *= m;

        // Special quick case: if m == 1, every pile is 1, so final x always 1 and only 1 configuration
        if (m == 1) {
            cout << 1 % MOD << "\n";
            continue;
        }

        // m == 2: enumerate all 2^n assignments; valMask bit i = 1 => pile i has 2 stones, else 1
        int fullMask = (1 << nGlob) - 1;
        ll cntFinalIs2 = 0;
        int totalAssign = 1 << nGlob;

        // global memo arrays sized for up to (1<<20). We avoid clearing by using 'stamp' per assignment.
        for (int valMask = 0; valMask < totalAssign; ++valMask) {
            valMaskGlob = valMask;
            ++stamp; // new timestamp for per-assignment memo
            unsigned char rootRes = solveMask(fullMask);
            if (rootRes == 2) ++cntFinalIs2;
        }

        // sum of finals = totalConfigs + cntFinalIs2  (because each final is 1 or 2)
        ll answer = (totalConfigs + cntFinalIs2) % MOD;
        cout << answer << "\n";
    }
    return 0;
}
