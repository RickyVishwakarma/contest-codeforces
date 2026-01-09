#include <bits/stdc++.h>
#include <numeric> 
using namespace std;
typedef long long ll;


int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int l, a, b;
        cin >> l >> a >> b;

        int g = gcd(l, b);
        int ans = l - g + (a % g);
        cout << ans << "\n";
    }
    return 0;
}
