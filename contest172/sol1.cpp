#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        unordered_set<int> st;
        int n = nums.size();
        int idx = n;

        // Find earliest index from where suffix is distinct
        for (int i = n - 1; i >= 0; i--) {
            if (st.count(nums[i])) {
                idx = i + 1;
                break;
            }
            st.insert(nums[i]);
        }

        // Already distinct
        if (idx == n) return 0;

        // Minimum operations (each removes 3 elements)
        return (idx + 2) / 3; // ceil(idx / 3)
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution sol;
    cout << sol.minimumOperations(nums) << "\n";

    return 0;
}
