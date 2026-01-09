#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        // Store (value, index) grouped by mod 3
        vector<pair<int,int>> r[3];
        for (int i = 0; i < n; i++) {
            r[nums[i] % 3].push_back({nums[i], i});
        }

        // Sort descending by value
        for (int i = 0; i < 3; i++) {
            sort(r[i].rbegin(), r[i].rend());
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int cur = nums[i] + nums[j];
                int need = (3 - (cur % 3)) % 3;

                for (auto &p : r[need]) {
                    int val = p.first;
                    int idx = p.second;

                    if (idx != i && idx != j) {
                        ans = max(ans, cur + val);
                        break; // largest valid found
                    }
                }
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 1, 5};
    cout << sol.maximumSum(nums1) << endl;  // ✅ 0

    vector<int> nums2 = {4, 2, 2, 3, 1};
    cout << sol.maximumSum(nums2) << endl;  // ✅ 9

    return 0;
}
