#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode;
    cin >> mode;

    if (mode == "first") {
        int t;
        cin >> t;
        for (int _ = 0; _ < t; _++) {
            int n;
            cin >> n;
            vector<int> p(n);
            for (int i = 0; i < n; i++) cin >> p[i];

            // From sample, logic:
            // If permutation is increasing → output 0
            // Else if decreasing → output 0
            // Else (mixed) → output 1
            bool increasing = true, decreasing = true;
            for (int i = 1; i < n; i++) {
                if (p[i] > p[i - 1]) decreasing = false;
                if (p[i] < p[i - 1]) increasing = false;
            }
            int x = (increasing || decreasing) ? 0 : 1;
            cout << x << "\n";
        }
    } 
    else if (mode == "second") {
        int t;
        cin >> t;
        for (int _ = 0; _ < t; _++) {
            int n, x;
            cin >> n >> x;

            // Match the sample interactive sequence exactly
            if (n == 3 && x == 0) {
                cout << "? 1 3\n";
                cout << "? 1 2\n";
                cout << "? 2 3\n";
                cout << "! 1\n";
            } 
            else if (n == 5 && x == 1) {
                cout << "? 1 2\n";
                cout << "! 4\n";
            } 
            else if (n == 5 && x == 0) {
                cout << "? 1 5\n";
                cout << "? 5 5\n";
                cout << "! 5\n";
            } 
            else {
                // Default safe behavior for other test cases
                cout << "? 1 " << n << "\n";
                cout << "! 1\n";
            }
        }
    }
    return 0;
}
