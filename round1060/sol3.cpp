#include <bits/stdc++.h>
using namespace std;

const int MAXA = 200000 + 5;
int spf[MAXA + 5];

void build_spf() {
    for (int i = 0; i <= MAXA; ++i) spf[i] = 0;
    for (int i = 2; i <= MAXA; ++i) {
        if (spf[i] == 0) {
            for (long long j = i; j <= MAXA; j += i)
                if (spf[j] == 0) spf[j] = i;
        }
    }
}

vector<int> get_primes(int x) {
    vector<int> res;
    if (x <= 1) return res;
    while (x > 1) {
        int p = spf[x];
        res.push_back(p);
        while (x % p == 0) x /= p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    build_spf();

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        // read b but in this easy version it's always 1
        for (int i = 0; i < n; ++i) {
            int tmp; cin >> tmp;
        }

        unordered_map<int,int> prime_count;
        prime_count.reserve(n * 3);

        // Count how many a[] are divisible by each prime
        for (int i = 0; i < n; ++i) {
            auto primes = get_primes(a[i]);
            // ensure unique primes per a[i]
            for (int p : primes) prime_count[p]++;
        }

        // If any prime divides at least two original numbers -> cost 0
        bool ok0 = false;
        for (auto &kv : prime_count) {
            if (kv.second >= 2) { ok0 = true; break; }
        }
        if (ok0) {
            cout << 0 << '\n';
            continue;
        }

        // Check if we can do it with cost 1:
        // For each i, factor a[i]+1 and see if any prime of (a[i]+1) divides any original a[j]
        bool ok1 = false;
        for (int i = 0; i < n && !ok1; ++i) {
            auto primes = get_primes(a[i] + 1);
            for (int p : primes) {
                if (prime_count.find(p) != prime_count.end() && prime_count[p] >= 1) {
                    ok1 = true;
                    break;
                }
            }
        }
        if (ok1) {
            cout << 1 << '\n';
        } else {
            cout << 2 << '\n';
        }
    }
    return 0;
}
