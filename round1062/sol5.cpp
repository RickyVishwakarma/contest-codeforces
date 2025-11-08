#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if(!(cin >> t)) return 0;
    while(t--){
        int n, k;
        ll x;
        cin >> n >> k >> x;
        vector<ll> a(n);
        for(int i=0;i<n;i++) cin >> a[i];
        sort(a.begin(), a.end());
        
        auto allowed_count_for_D = [&](ll D)->ll{
            if(D <= 0) return x + 1; // all integer positions allowed
            // forbidden intervals are [ai-(D-1), ai+(D-1)] inclusive
            ll expand = D - 1;
            vector<pair<ll,ll>> segs;
            segs.reserve(n);
            for(ll ai : a){
                ll L = ai - expand;
                ll R = ai + expand;
                if(R < 0 || L > x) continue; // outside [0,x]
                L = max(L, 0LL);
                R = min(R, x);
                segs.emplace_back(L, R);
            }
            if(segs.empty()) return x + 1;
            sort(segs.begin(), segs.end());
            ll covered = 0;
            ll curL = segs[0].first, curR = segs[0].second;
            for(size_t i=1;i<segs.size();++i){
                if(segs[i].first <= curR + 1){
                    curR = max(curR, segs[i].second);
                } else {
                    covered += (curR - curL + 1);
                    curL = segs[i].first;
                    curR = segs[i].second;
                }
            }
            covered += (curR - curL + 1);
            ll total_positions = x + 1;
            ll allowed = total_positions - covered;
            return allowed;
        };
        
        // Binary search maximum integer D >= 1 such that allowed_count_for_D(D) >= k
        ll lo = 1, hi = x + 1, best = 0;
        while(lo <= hi){
            ll mid = (lo + hi) >> 1;
            if(allowed_count_for_D(mid) >= k){
                best = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        
        vector<ll> ans;
        ans.reserve(k);
        if(best == 0){
            // D = 0 -> any k distinct integers in [0,x], constraint guarantees k-1 <= x
            for(int i=0;i<k;i++) ans.push_back(i);
        } else {
            ll expand = best - 1;
            // build merged forbidden intervals
            vector<pair<ll,ll>> segs;
            for(ll ai : a){
                ll L = ai - expand;
                ll R = ai + expand;
                if(R < 0 || L > x) continue;
                L = max(L, 0LL);
                R = min(R, x);
                segs.emplace_back(L, R);
            }
            sort(segs.begin(), segs.end());
            vector<pair<ll,ll>> merged;
            for(auto &s: segs){
                if(merged.empty() || s.first > merged.back().second + 1){
                    merged.push_back(s);
                } else {
                    merged.back().second = max(merged.back().second, s.second);
                }
            }
            // allowed intervals are the gaps between merged forbidden intervals
            ll cur = 0;
            size_t idx = 0;
            while((int)ans.size() < k && cur <= x){
                ll nextForbiddenL = (idx < merged.size() ? merged[idx].first : x+1);
                // allowed block: [cur, nextForbiddenL-1]
                if(cur <= nextForbiddenL - 1){
                    ll L = cur;
                    ll R = nextForbiddenL - 1;
                    for(ll p = L; p <= R && (int)ans.size() < k; ++p){
                        ans.push_back(p);
                    }
                }
                // skip forbidden block
                if(idx < merged.size()){
                    cur = merged[idx].second + 1;
                    ++idx;
                } else break;
            }
            // in case still not enough (shouldn't happen because best was valid), but safe:
            ll p = x;
            while((int)ans.size() < k){
                // fill from the rightmost allowed positions (rare fallback)
                if(find(ans.begin(), ans.end(), p) == ans.end()) ans.push_back(p);
                --p;
            }
        }
        
        // Output k integers (any order)
        for(int i=0;i<k;i++){
            if(i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
