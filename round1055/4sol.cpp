#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int stepsFor(ll x) {
    int moves = 0;
    while (x > 1) {
        x /= 2;    
        moves++;
        if (x == 1) break;
        x += 1;     
    }
    return moves;
}

inline bool isSpecial(ll x) {
    if (x < 3) return false;
    ll y = x - 1;
    return (y & (y - 1)) == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; 
    cin >> T;
    while (T--) {
        int n, q;
        cin >> n >> q;
        vector<ll> arr(n+1);
        for (int i = 1; i <= n; i++) cin >> arr[i];

        vector<ll> prefScore(n+1, 0);
        vector<int> prefSpecial(n+1, 0);

        for (int i = 1; i <= n; i++) {
            prefScore[i] = prefScore[i-1] + stepsFor(arr[i]);
            prefSpecial[i] = prefSpecial[i-1] + (isSpecial(arr[i]) ? 1 : 0);
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            ll base = prefScore[r] - prefScore[l-1];
            int specials = prefSpecial[r] - prefSpecial[l-1];
            base += specials / 2; 
            cout << base << "\n";
        }
    }
    return 0;
}
