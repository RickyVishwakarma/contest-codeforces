#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        for (int &v: arr) cin >> v;
        unordered_map<int,int> freq;
        freq.reserve(n * 2);
        for (int v: arr) freq[v]++;
        int maxFreq = 0;
        for (auto &x : freq) maxFreq = max(maxFreq, x.second);
        if (maxFreq <= k) {
            cout << 0 << "\n";
            continue;
        }
        if (freq.size() == 1) {
            cout << max(0, n - k) << "\n";
            continue;
        }
        long long ops = 0;
        while (true) {
            unordered_map<int,int> temp;
            temp.reserve(freq.size() * 2);
            for (auto &p : freq) {
                int energy = p.first;
                int cnt = p.second;
                if (cnt > 0) {
                    temp[energy] += 1;
                }
                if (cnt > 1) {
                    temp[energy + 1] += (cnt - 1);
                }
            }
            ops++;
            freq.swap(temp);
            maxFreq = 0;
            for (auto &p : freq) maxFreq = max(maxFreq, p.second);
            if (maxFreq <= k) break;
            if (ops >= n) break; 
        }
        cout << ops << "\n";
    }
    return 0;
}
