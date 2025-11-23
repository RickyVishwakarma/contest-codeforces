#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k, q;
        cin >> n >> k >> q;

        vector<int> c(q), L(q), R(q);
        for (int i = 0; i < q; i++) {
            cin >> c[i] >> L[i] >> R[i];
            --L[i];   // to 0-based
            --R[i];
        }

        // Mark which positions belong to some c=1 or some c=2 segment
        vector<int> inC1(n, 0), inC2(n, 0);
        for (int i = 0; i < q; i++) {
            if (c[i] == 1) {
                for (int j = L[i]; j <= R[i]; j++)
                    inC1[j] = 1;
            } else {
                for (int j = L[i]; j <= R[i]; j++)
                    inC2[j] = 1;
            }
        }

        vector<int> a(n, -1);

        // Positions NOT in any c=1 segment can be < k.
        vector<int> smallable;
        for (int i = 0; i < n; i++) {
            if (!inC1[i]) smallable.push_back(i);
        }

        // Put 0..k-1 cyclically on smallable positions.
        // This guarantees for every c=2 segment there are all 0..k-1
        // (since a valid solution exists and there are enough such positions).
        for (int idx = 0; idx < (int)smallable.size(); idx++) {
            int pos = smallable[idx];
            a[pos] = idx % k;  // 0..k-1
        }

        // All remaining positions (still -1) become some BIG > k.
        const int BIG = k + 1;
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) a[i] = BIG;
        }

        // Now no element equals k anywhere.
        // All c=2 segments have MEX = k (0..k-1 present, k absent).

        // Fix c=1 segments: we must make min = k.
        // We can only safely place k at positions NOT in any c=2 segment,
        // otherwise we would break MEX = k.
        for (int i = 0; i < q; i++) {
            if (c[i] != 1) continue;

            int l = L[i], r = R[i];

            bool hasK = false;
            for (int j = l; j <= r; j++) {
                if (a[j] == k) {
                    hasK = true;
                    break;
                }
            }
            if (hasK) continue;

            // choose some position in [l,r] not in c2
            int chosen = -1;
            for (int j = l; j <= r; j++) {
                if (!inC2[j]) {
                    chosen = j;
                    break;
                }
            }

            // problem guarantees a valid solution exists, so chosen != -1
            if (chosen == -1) {
                chosen = l; // fallback, shouldn't happen
            }

            a[chosen] = k;
        }

        // Print answer
        for (int i = 0; i < n; i++) {
            cout << a[i] << (i + 1 < n ? ' ' : '\n');
        }
    }

    return 0;
}
