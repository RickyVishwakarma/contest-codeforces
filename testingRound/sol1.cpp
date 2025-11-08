#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    cin >> phase;

    if (phase == "first") {
        int n;
        cin >> n;
        vector<int> nums(n);
        for (int i = 0; i < n; i++) cin >> nums[i];

        string result;
        result.reserve(n);
        for (int val : nums)
            result.push_back('a' + val - 1);

        cout << result << '\n';
    } 
    else {
        string s;
        cin >> s;
        int n = (int)s.size();
        cout << n << '\n';
        for (int i = 0; i < n; i++) {
            cout << (s[i] - 'a' + 1);
            if (i + 1 < n) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
