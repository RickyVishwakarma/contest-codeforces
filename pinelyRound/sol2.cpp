// Brute-force validator for "Make Connected" — correct but exponential
// Good for testing small sample inputs (like the one you pasted).
// NOT suitable for the full constraints (n up to 100) in contest.

#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> G;

bool has_triplet(const vector<string>& g) {
    int n = g.size();
    for (int i=0;i<n;i++) {
        for (int j=0;j+2<n;j++) {
            if (g[i][j]=='#' && g[i][j+1]=='#' && g[i][j+2]=='#') return true;
        }
    }
    for (int j=0;j<n;j++) {
        for (int i=0;i+2<n;i++) {
            if (g[i][j]=='#' && g[i+1][j]=='#' && g[i+2][j]=='#') return true;
        }
    }
    return false;
}

bool is_connected_and_nonempty(const vector<string>& g) {
    int n = g.size();
    vector<pair<int,int>> blacks;
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (g[i][j]=='#') blacks.emplace_back(i,j);
    if (blacks.empty()) return false;
    set<pair<int,int>> seen;
    queue<pair<int,int>>q;
    seen.insert(blacks[0]); q.push(blacks[0]);
    int cnt = 0;
    while (!q.empty()) {
        auto [r,c] = q.front(); q.pop(); cnt++;
        const int dr[4] = {1,-1,0,0};
        const int dc[4] = {0,0,1,-1};
        for (int k=0;k<4;k++) {
            int nr=r+dr[k], nc=c+dc[k];
            if (0<=nr && nr<n && 0<=nc && nc<n && g[nr][nc]=='#' && !seen.count({nr,nc})) {
                seen.insert({nr,nc});
                q.push({nr,nc});
            }
        }
    }
    return cnt == (int)blacks.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin>>t)) return 0;
    while (t--) {
        cin>>n;
        G.assign(n,"");
        for (int i=0;i<n;i++) cin>>G[i];

        // collect white positions
        vector<pair<int,int>> whites;
        for (int i=0;i<n;i++) for (int j=0;j<n;j++) if (G[i][j]=='.') whites.emplace_back(i,j);

        bool possible = false;
        int m = whites.size();
        // try all subsets of whites to paint (0..2^m-1)
        // Note: painting none is allowed (we keep original blacks)
        // but the final grid must have >=1 black (checked later).
        // For m up to ~20 this is fine for testing; bigger m will be slow.
        long long limit = 1LL<<m;
        if (m <= 22) { // safety cutoff for runtime
            for (long long mask=0; mask<limit; ++mask) {
                vector<string> g = G;
                for (int k=0;k<m;k++) if (mask & (1LL<<k)) {
                    auto [r,c] = whites[k];
                    g[r][c] = '#';
                }
                // check rules
                if (has_triplet(g)) continue;
                if (!is_connected_and_nonempty(g)) continue;
                possible = true; break;
            }
        } else {
            // If too many whites for brute force, fallback to a heuristic check:
            // We won't claim correctness here; ask me to provide the efficient solution.
            cout << "UNKNOWN\n";
            continue;
        }

        cout << (possible ? "YES\n" : "NO\n");
    }
    return 0;
}
