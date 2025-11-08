#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, target;
        cin >> n >> target;
        vector<int> data(n);
        vector<int> freq(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            cin >> data[i];
            if (data[i] <= n) {
                freq[data[i]]++;
            }
        }

        int moves = 0;

        if (target == 0) {
       
            moves = (freq[0] > 0 ? 1 : 0);
        } else {
          
            bool gapFound = false;
            for (int v = 0; v < target; ++v) {
                if (freq[v] == 0) {
                    gapFound = true;
                    break;
                }
            }
            if (gapFound) moves += 1;

       
            if (freq[target] > 0) moves += 1;
        }

        cout << moves << "\n";
    }
    return 0;
}
