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
        vector<int> a(n), b(n);
        for (int &x : a) cin >> x;
        for (int &x : b) cin >> x;

        int xa = 0, xb = 0;
        for (int i = 0; i < n; i++) {
            xa ^= a[i];
            xb ^= b[i];
        }

        // If their total XOR is the same, nobody can ever lead → always tie
        if (xa == xb) {
            cout << "Tie\n";
            continue;
        }

        // We track only the last bit of Ajisai's score (0 or 1)
        int startBit = xa;

        // dpNext[s] = result if current bit = s and we still have future turns
        // 0 = Ajisai wins, 1 = Mai wins, 2 = no forced win (tie)
        int dpNext[2], dpNow[2];

        // After the last turn: if bit = 1 → Ajisai wins, if 0 → Mai wins
        dpNext[0] = 1; // bit 0 → Mai
        dpNext[1] = 0; // bit 1 → Ajisai

        // Process turns backwards
        for (int i = n; i >= 1; i--) {
            int canFlip = (a[i - 1] ^ b[i - 1]); // 1 if this position can flip the bit

            if (!canFlip) {
                // This move can't change the deciding bit
                dpNow[0] = dpNext[0];
                dpNow[1] = dpNext[1];
            } else {
                int turn = (i % 2 == 1 ? 0 : 1); // 0 = Ajisai, 1 = Mai

                for (int s = 0; s < 2; s++) {
                    int keepRes = dpNext[s];
                    int flipRes = dpNext[s ^ 1];

                    if (turn == 0) { // Ajisai's move
                        if (keepRes == 0 || flipRes == 0)
                            dpNow[s] = 0;           // she can force win
                        else if (keepRes == 1 && flipRes == 1)
                            dpNow[s] = 1;           // Mai always wins
                        else
                            dpNow[s] = 2;           // no forced winner
                    } else {        // Mai's move
                        if (keepRes == 1 || flipRes == 1)
                            dpNow[s] = 1;
                        else if (keepRes == 0 && flipRes == 0)
                            dpNow[s] = 0;
                        else
                            dpNow[s] = 2;
                    }
                }
            }

            dpNext[0] = dpNow[0];
            dpNext[1] = dpNow[1];
        }

        int finalRes = dpNext[startBit];
        if (finalRes == 0)      cout << "Ajisai\n";
        else if (finalRes == 1) cout << "Mai\n";
        else                    cout << "Tie\n";
    }

    return 0;
}
