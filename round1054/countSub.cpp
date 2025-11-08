#include <bits/stdc++.h>
using namespace std;


auto countAtMost = [&](const vector<int>& arr, int K, int L, int R) {
    if (K < 0) return 0LL; 

    long long total = 0;
    int n = arr.size();
    map<int,int> freq;      
    int distinct = 0;
    int right = -1;


    for (int left = 0; left < n; ++left) {
        while (right + 1 < n) {
            int nxt = arr[right + 1];
            if (freq[nxt] == 0 && distinct == K) break;
            ++right;
            if (++freq[arr[right]] == 1) distinct++;
        }

       
        int minLen = L, maxLen = R;
        int lo = left + minLen - 1;
        int hi = min(right, left + maxLen - 1);

        if (hi >= lo) total += (hi - lo + 1);

        // shrink from left
        if (--freq[arr[left]] == 0) {
            freq.erase(arr[left]);
            distinct--;
        }
    }
    return total;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k, l, r;
        cin >> n >> k >> l >> r;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = countAtMost(a, k, l, r) - countAtMost(a, k - 1, l, r);
        cout << ans << "\n";
    }
}
