#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        sort(a.begin(), a.end(), greater<ll>()); // sort descending

        ll alice = 0, bob = 0;
        bool turn = 0; // 0 = Alice, 1 = Bob
        ll cnt = 0;    // number of elements ≥ current value

        for (int i = 0; i < n; ) {
            ll val = a[i];
            int j = i;
            while (j < n && a[j] == val) j++;
            cnt += (j - i); // add frequency of this value

            ll nextVal = (j < n ? a[j] : 0);
            ll delta = val - nextVal; // number of levels in this interval

            // distribute delta turns
            ll aliceMoves = (delta + (turn == 0)) / 2;
            ll bobMoves   = delta / 2;

            alice += aliceMoves * cnt;
            bob   += bobMoves   * cnt;

            // update whose turn next
            if (delta % 2 == 1) turn ^= 1;

            i = j;
        }

        cout << alice << " " << bob << "\n";
    }
}
