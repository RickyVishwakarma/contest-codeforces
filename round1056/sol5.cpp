#include <bits/stdc++.h>
using namespace std;

// helper for fast I/O
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    fastio;
    int t; 
    cin >> t;
    while (t--) {
        long long rows, cols; 
        int tokCount;
        cin >> rows >> cols >> tokCount;

        // idea: for n == 1, only tokens at column 2 matter
        // otherwise, each column >= 2 works like a pile in Nim
        if (rows == 1) {
            bool oddInCol2 = false;
            for (int i = 0; i < tokCount; ++i) {
                int r, c; 
                cin >> r >> c;
                if (c == 2) oddInCol2 = !oddInCol2;
            }
            cout << (oddInCol2 ? "Mimo\n" : "Yuyu\n");
            continue;
        }

        // track parity (odd/even count) for columns >= 2
        unordered_map<int, bool> columnParity;
        columnParity.reserve(tokCount * 2);

        for (int i = 0; i < tokCount; ++i) {
            int r, c;
            cin >> r >> c;
            if (c >= 2) {
                columnParity[c] = !columnParity[c];
            }
        }

        // if any column has odd count of tokens => first player wins
        bool mimoWins = false;
        for (auto &p : columnParity) {
            if (p.second) {
                mimoWins = true;
                break;
            }
        }

        cout << (mimoWins ? "Mimo\n" : "Yuyu\n");
    }
    return 0;
}
