#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long modpow(long long x, long long y) {
    long long r = 1;
    x %= MOD;
    while (y) {
        if (y & 1) r = r * x % MOD;
        x = x * x % MOD;
        y >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<int> b(n);
    for(int i = 0; i < n; i++) cin >> b[i];

    // Each student has some initial cards.
    vector<vector<long long>> cards(m + 1);
    vector<long long> free_cards;

    for(int i = 0; i < n; i++) {
        if (b[i] == 0) free_cards.push_back(a[i]);
        else cards[b[i]].push_back(a[i]);
    }

    int k = free_cards.size();

    // Expected number of cards: initial count + sum over free cards (probability student gets it)
    vector<long long> ans(m + 1);
    for(int i = 1; i <= m; i++)
        ans[i] = cards[i].size();

    // Precompute smallest card of each student
    vector<long long> smallest(m + 1, 0);
    for(int i = 1; i <= m; i++) {
        sort(cards[i].begin(), cards[i].end());
        if (!cards[i].empty())
            smallest[i] = cards[i][0];
    }

    long long inv_k = modpow(k, MOD - 2);

    // For each free card c, determine probability each student wins it.
    for(long long c : free_cards) {

        // Step 1: compute candidate chosen card for each student
        vector<long long> pick(m + 1);
        for(int s = 1; s <= m; s++) {
            long long best_div = -1;
            for(long long v : cards[s]) {
                if (v % c == 0) {
                    if (best_div == -1 || v < best_div)
                        best_div = v;
                }
            }
            if (best_div != -1) pick[s] = best_div;
            else pick[s] = smallest[s]; 
        }

        // Step 2: find all divisible picks
        long long winner_card = -1;
        for(int s = 1; s <= m; s++) {
            if (pick[s] % c == 0) {
                if (winner_card == -1 || pick[s] < winner_card)
                    winner_card = pick[s];
            }
        }

        // If no one can win → skip
        if (winner_card == -1) continue;

        // Step 3: compute number of students who choose winner_card as divisible
        vector<long long> good;
        for(int s = 1; s <= m; s++) {
            if (pick[s] == winner_card && pick[s] % c == 0)
                good.push_back(s);
        }

        int cnt = good.size();
        long long inv_cnt = modpow(cnt, MOD - 2);

        // Step 4: distribute expected value
        for(int s : good) {
            ans[s] = (ans[s] + inv_k * inv_cnt) % MOD;
        }
    }

    for(int i = 1; i <= m; i++)
        cout << ans[i] % MOD << " ";
    cout << "\n";
    return 0;
}
