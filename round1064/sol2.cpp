#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        long long A, B, N;
        cin >> A >> B >> N;

        // If the tab width cap is at least screen size,
        // all x's always end up on the right edge.
        if (B >= A) {
            cout << 1 << "\n";
            continue;
        }

        // Maximum number of tabs that still keep len = a/m <= b
        long long limit = A / B;

        // If we never reach the phase where len becomes exactly B
        // we can finish with a single movement.
        if (N <= limit) {
            cout << 1 << "\n";
        } else {
            // Otherwise len changes once → need two cursor adjustments
            cout << 2 << "\n";
        }
    }
    return 0;
}
