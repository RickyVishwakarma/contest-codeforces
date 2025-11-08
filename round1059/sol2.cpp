#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string &s) {
    int l = 0, r = (int)s.size() - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return false;
    }
    return true;
}
bool isNonDecreasing(const string &s) {
    for (int i = 1; i < (int)s.size(); ++i)
        if (s[i] < s[i-1]) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        bool any = false;
        long long bestSum = -1;
        int bestMask = 0;
        int bestK = 0;

        for (int mask = 0; mask < (1 << n); ++mask) {
            string p = "", x = "";
            long long sumIdx = 0;
            int k = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    p.push_back(s[i]);
                    sumIdx += (i + 1);
                    ++k;
                } else {
                    x.push_back(s[i]);
                }
            }
            if (isNonDecreasing(p) && isPalindrome(x)) {
                // prefer larger sum of indices, then larger k, then larger mask
                if (!any || make_tuple(sumIdx, k, mask) > make_tuple(bestSum, bestK, bestMask)) {
                    any = true;
                    bestSum = sumIdx;
                    bestMask = mask;
                    bestK = k;
                }
            }
        }

        if (!any) {
            cout << -1 << '\n';
        } else {
            cout << bestK << '\n';
            if (bestK > 0) {
                bool first = true;
                for (int i = 0; i < n; ++i) {
                    if (bestMask & (1 << i)) {
                        if (!first) cout << ' ';
                        cout << (i + 1);
                        first = false;
                    }
                }
                cout << '\n';
            } else {
                cout << '\n';
            }
        }
    }
    return 0;
}
