#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; 
    cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;
        sort(a.begin(), a.end());

        long long best = 0;
        for (int i = 0; i < n/2; i++) {
            int left = 2*i, right = 2*i + 1;
            best = max(best, a[right] - a[left]);
        }
        cout << best << "\n";
    }
    return 0;
}
