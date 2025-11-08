#include <bits/stdc++.h>
using namespace std;

long long calcCost(const string &s, char target) {
    vector<int> idx;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == target) idx.push_back(i);
    }
    if (idx.empty()) return 0;  

    int k = idx.size();
\
    for (int i = 0; i < k; i++) idx[i] -= i;

    nth_element(idx.begin(), idx.begin() + k/2, idx.end());
    int med = idx[k/2];

    long long moves = 0;
    for (int v : idx) moves += abs(v - med);
    return moves;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

      
        long long movesA = calcCost(s, 'a');
        long long movesB = calcCost(s, 'b');

        cout << min(movesA, movesB) << "\n";
    }
    return 0;
}
