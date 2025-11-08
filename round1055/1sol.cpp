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

        vector<int> target(n);
        for (int i = 0; i < n; i++) {
            cin >> target[i];
        }
        unordered_set<int> uniq;
        for (int x : target) uniq.insert(x);

        int distinct = uniq.size();
        int moves = 2 * distinct - 1;
        cout << moves << "\n";
    }
    return 0;
}
