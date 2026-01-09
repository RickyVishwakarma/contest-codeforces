#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    unordered_set<string> vis;
    long long ans = 0;

    void dfs(string s, vector<int>& nums) {
        if (vis.count(s)) return;
        vis.insert(s);

        long long score = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') score += nums[i];
        }
        ans = max(ans, score);

        for (int i = 0; i + 1 < s.size(); i++) {
            if (s[i] == '0' && s[i + 1] == '1') {
                swap(s[i], s[i + 1]);
                dfs(s, nums);
                swap(s[i], s[i + 1]);
            }
        }
    }
    long long maximumScore(vector<int>& nums, string s) {
        dfs(s, nums);
        return ans;
        // int n = nums.size();
        // vector<int>ones;
        // for(int i = 0 ; i < n ; i++){
        //     if(s[i] == '1'){
        //         ones.push_back(nums[i]);
        //     }
        // }

        // int k = ones.size();
        // if(k == 0) return 0;

        // vector<int>all = nums;
        // sort(all.begin(),all.end() , greater<int>());
        // long long ans = 0;
        // for(int i = 0 ; i < k ; i++){
        //     ans += all[i];
        // }
        // return ans;
        // priority_queue<int, vector<int>, greater<int>> pq;
        // int ones = 0;

        // for (char c : s) {
        //     if (c == '1') ones++;
        // }

        // for (int x : nums) {
        //     pq.push(x);
        //     if (pq.size() > ones) {
        //         pq.pop();
        //     }
        // }

        // long long ans = 0;
        // while (!pq.empty()) {
        //     ans += pq.top();
        //     pq.pop();
        // }

        // return ans;
    }
};


int main() {
    Solution sol;

    vector<int> nums = {2 ,1 , 5 , 2 , 3};
    string s = "01010";

    long long result = sol.maximumScore(nums, s);
    cout << result << endl;

    return 0;
}
