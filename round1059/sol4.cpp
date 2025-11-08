#include <bits/stdc++.h>
using namespace std;

long long query(int type, int l, int r) {
    cout << type << " " << l << " " << r << endl;
    cout.flush();
    long long x;
    cin >> x;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        // Step 1: get total sums
        long long sumP = query(1, 1, n);
        long long sumA = query(2, 1, n);

        long long len = sumA - sumP; // length of modified range

        int lo = 1, hi = n, l = -1;

        // Step 2: binary search for start of modified segment
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            long long prefixP = query(1, 1, mid);
            long long prefixA = query(2, 1, mid);
            long long diff = prefixA - prefixP;

            if (diff == 0) {
                lo = mid + 1;
            } else {
                l = mid;
                hi = mid - 1;
            }
        }

        int r = l + len - 1;

        cout << "! " << l << " " << r << endl;
        cout.flush();
    }
}
