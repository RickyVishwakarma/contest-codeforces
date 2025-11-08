#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ll = long long;

// patience algorithm producing parent links and last positions
int lis_patience(const vi &a, vi &parent, vi &last_pos) {
    int m = (int)a.size() - 1; // 1-based array
    vector<int> tails;         // actual tail values (not needed except for binary search)
    vector<int> pos;           // pos[k] = index i that ends a LIS of length k+1
    parent.assign(m+1, -1);

    for (int i = 1; i <= m; ++i) {
        int val = a[i];
        auto it = lower_bound(tails.begin(), tails.end(), val);
        int k = int(it - tails.begin());
        if (it == tails.end()) {
            tails.push_back(val);
            pos.push_back(i);
        } else {
            *it = val;
            pos[k] = i;
        }
        parent[i] = (k == 0 ? -1 : pos[k-1]);
    }
    last_pos = pos; // pos[k] gives last index for subseq length k+1
    return (int)tails.size();
}

vi reconstruct(const vi &parent, const vi &last_pos, int L) {
    vi seq;
    if (L <= 0) return seq;
    int cur = last_pos[L-1];
    while (cur != -1) {
        seq.push_back(cur);
        cur = parent[cur];
    }
    reverse(seq.begin(), seq.end());
    return seq;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        int m = n * n + 1;
        vi a(m+1);
        for (int i = 1; i <= m; ++i) cin >> a[i];

        vi parent, lastpos;
        int L = lis_patience(a, parent, lastpos);
        if (L >= n+1) {
            vi seq = reconstruct(parent, lastpos, L);
            seq.resize(n+1);
            for (int i = 0; i < (int)seq.size(); ++i) {
                if (i) cout << ' ';
                cout << seq[i];
            }
            cout << '\n';
            continue;
        }

        // Otherwise find LDS by running LIS on negated values
        vi b(m+1);
        for (int i = 1; i <= m; ++i) b[i] = -a[i];
        int L2 = lis_patience(b, parent, lastpos);
        // L2 must be >= n+1 by theory
        vi seq = reconstruct(parent, lastpos, L2);
        seq.resize(n+1);
        for (int i = 0; i < (int)seq.size(); ++i) {
            if (i) cout << ' ';
            cout << seq[i];
        }
        cout << '\n';
    }
    return 0;
}
