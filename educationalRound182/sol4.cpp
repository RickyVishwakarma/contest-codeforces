// Author rick17

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INFLL = (1LL<<62);
const int MAXC = 200000;
const ll MOD_UNUSED = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n; ll y;
        cin >> n >> y;
        vector<int> c(n);
        int maxc = 0;
        for (int i = 0; i < n; ++i) {
            cin >> c[i];
            maxc = max(maxc, c[i]);
        }

   
        vector<int> freq_old(maxc+1);
        for (int v : c) freq_old[v]++;

        ll best = LLONG_MIN;


        int B = max(450, (int)(sqrt(maxc) + 2));


        for (int x = 2; x <= B; ++x) {

            unordered_map<int,int> need;
            need.reserve(n*2);
            ll sum_p = 0;
            for (int v : c) {
                int p = (v + x - 1) / x;
                sum_p += p;
                need[p]++;
            }
            ll new_tags = 0;
            for (auto &pr : need) {
                int price = pr.first;
                int cnt_need = pr.second;
                int cnt_old = (price <= maxc ? freq_old[price] : 0);
                if (cnt_need > cnt_old) new_tags += (cnt_need - cnt_old);
            }
            ll income = sum_p - new_tags * y;
            best = max(best, income);
        }
        int maxP = maxc / (B+1) + 2;
     
        vector<int> candidates;
        candidates.reserve(2 * maxc / B + 10);
        for (int v = 0; v < n; ++v) {
            int val = c[v];
            int k = 1;
            while (k <= val) {
                int x_low = val / k; // floor
                if (x_low <= B) break; // interested in x > B only
                candidates.push_back(x_low);
              
                int nxt = val / x_low + 1;
                k = nxt;
            }
        }
   
        candidates.push_back(B+1);

        candidates.push_back(maxc);
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());


        for (int x : candidates) {
            if (x <= B) continue;

            unordered_map<int,int> need;
            need.reserve(n*2);
            ll sum_p = 0;
            for (int v : c) {
                int p = (v + x - 1) / x;
                sum_p += p;
                need[p]++;
            }
            ll new_tags = 0;
            for (auto &pr : need) {
                int price = pr.first;
                int cnt_need = pr.second;
                int cnt_old = (price <= maxc ? freq_old[price] : 0);
                if (cnt_need > cnt_old) new_tags += (cnt_need - cnt_old);
            }
            ll income = sum_p - new_tags * y;
            best = max(best, income);
        }

        
        cout << best << '\n';
    }
    return 0;
}
