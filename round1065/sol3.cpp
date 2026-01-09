// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int T;
//     cin >> T;
//     while (T--) {
//         int n;
//         cin >> n;
//         vector<long long> a(n), b(n);
//         for (int i = 0; i < n; ++i) cin >> a[i];
//         for (int i = 0; i < n; ++i) cin >> b[i];

//         long long xorA = 0, xorB = 0;
//         for (int i = 0; i < n; ++i) {
//             xorA ^= a[i];
//             xorB ^= b[i];
//         }
//         long long D = xorA ^ xorB;

//         // If D == 0, scores are always equal → Tie.
//         if (D == 0) {
//             cout << "Tie\n";
//             continue;
//         }

//         // k = most significant bit of D
//         int k = 63 - __builtin_clzll(D);

//         // initial bit at position k of Ajisai's score
//         int s0 = (xorA >> k) & 1;

//         // dp_next[s]: result from future turns (i+1..n) given current bit s
//         // 0 = Ajisai, 1 = Mai, 2 = Tie
//         int dp_next[2], dp_cur[2];
//         dp_next[0] = 1; // if game ended now with s=0 → Mai wins
//         dp_next[1] = 0; // if game ended now with s=1 → Ajisai wins

//         for (int i = n; i >= 1; --i) {
//             // d[i] = a[i-1] ^ b[i-1], we only care about bit k
//             int dik = ((a[i-1] ^ b[i-1]) >> k) & 1;

//             if (dik == 0) {
//                 // this turn can't change bit s
//                 dp_cur[0] = dp_next[0];
//                 dp_cur[1] = dp_next[1];
//             } else {
//                 int P = (i % 2 == 1 ? 0 : 1); // 0: Ajisai, 1: Mai
//                 for (int s = 0; s <= 1; ++s) {
//                     int r_pass = dp_next[s];
//                     int r_flip = dp_next[s ^ 1];

//                     if (P == 0) { // Ajisai's move
//                         if (r_pass == 0 || r_flip == 0)
//                             dp_cur[s] = 0;           // she can force win
//                         else if (r_pass == 1 && r_flip == 1)
//                             dp_cur[s] = 1;           // Mai always wins
//                         else
//                             dp_cur[s] = 2;           // Tie
//                     } else {       // Mai's move
//                         if (r_pass == 1 || r_flip == 1)
//                             dp_cur[s] = 1;
//                         else if (r_pass == 0 && r_flip == 0)
//                             dp_cur[s] = 0;
//                         else
//                             dp_cur[s] = 2;
//                     }
//                 }
//             }
//             dp_next[0] = dp_cur[0];
//             dp_next[1] = dp_cur[1];
//         }

//         int res = dp_next[s0];
//         if (res == 0) cout << "Ajisai\n";
//         else if (res == 1) cout << "Mai\n";
//         else cout << "Tie\n";
//     }

//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;
        vector<long long> A(n), B(n);

        for (auto &x : A) cin >> x;
        for (auto &x : B) cin >> x;

        long long xA = 0, xB = 0;
        for (int i = 0; i < n; i++) {
            xA ^= A[i];
            xB ^= B[i];
        }

        long long D = xA ^ xB;

        // If final XORs always match → no one can force a win
        if (D == 0) {
            cout << "Tie\n";
            continue;
        }

        // Decide the bit that matters (highest bit that differs)
        int bit = 63 - __builtin_clzll(D);

        // Current value of that bit in Ajisai's score
        int start = (xA >> bit) & 1;

        // dp[s] = winner if current bit = s and game from next position
        // 0: Ajisai wins, 1: Mai wins, 2: nobody can force win (tie)
        int dp_next[2] = {1, 0}, dp_now[2];

        for (int i = n - 1; i >= 0; i--) {
            int canFlip = ((A[i] ^ B[i]) >> bit) & 1;  // this index can flip or not

            if (!canFlip) {          // no control on this bit
                dp_now[0] = dp_next[0];
                dp_now[1] = dp_next[1];
            } else {
                int turn = (i % 2 == 0) ? 0 : 1;   // 0: Ajisai, 1: Mai

                for (int s = 0; s < 2; s++) {
                    int p = dp_next[s];        // keep bit
                    int q = dp_next[s ^ 1];    // flip bit

                    if (turn == 0) { // Ajisai plays
                        if (p == 0 || q == 0)       dp_now[s] = 0;
                        else if (p == 1 && q == 1)  dp_now[s] = 1;
                        else                        dp_now[s] = 2;
                    } else {       // Mai plays
                        if (p == 1 || q == 1)       dp_now[s] = 1;
                        else if (p == 0 && q == 0)  dp_now[s] = 0;
                        else                        dp_now[s] = 2;
                    }
                }
            }
            dp_next[0] = dp_now[0];
            dp_next[1] = dp_now[1];
        }

        int result = dp_next[start];

        if (result == 0) cout << "Ajisai\n";
        else if (result == 1) cout << "Mai\n";
        else cout << "Tie\n";
    }
    return 0;
}
