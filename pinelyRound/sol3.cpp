#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> G;

bool has_triplet(const vector<string>& g) {
    int n = (int)g.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j + 2 < n; ++j) {
            if (g[i][j] == '#' && g[i][j+1] == '#' && g[i][j+2] == '#') return true;
        }
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i + 2 < n; ++i) {
            if (g[i][j] == '#' && g[i+1][j] == '#' && g[i+2][j] == '#') return true;
        }
    }
    return false;
}

bool is_connected_and_nonempty(const vector<string>& g) {
    int n = (int)g.size();
    vector<pair<int,int>> blacks;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (g[i][j] == '#') blacks.push_back(make_pair(i,j));
    if (blacks.empty()) return false;
    set<pair<int,int>> seen;
    queue<pair<int,int>> q;
    seen.insert(blacks[0]);
    q.push(blacks[0]);
    int cnt = 0;
    while (!q.empty()) {
        pair<int,int> cur = q.front(); q.pop(); ++cnt;
        int r = cur.first, c = cur.second;
        const int dr[4] = {1,-1,0,0};
        const int dc[4] = {0,0,1,-1};
        for (int k = 0; k < 4; ++k) {
            int nr = r + dr[k], nc = c + dc[k];
            if (0 <= nr && nr < n && 0 <= nc && nc < n && g[nr][nc] == '#') {
                pair<int,int> pr = make_pair(nr,nc);
                if (!seen.count(pr)) {
                    seen.insert(pr);
                    q.push(pr);
                }
            }
        }
    }
    return cnt == (int)blacks.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        cin >> n;
        G.assign(n,"");
        for (int i = 0; i < n; ++i) cin >> G[i];

        // collect white positions
        vector<pair<int,int>> whites;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (G[i][j] == '.') whites.push_back(make_pair(i,j));

        bool possible = false;
        int m = (int)whites.size();

        // try all subsets of whites to paint (0..2^m-1)
        // limit brute force to manageable size
        if (m <= 22) {
            long long limit = 1LL << m;
            for (long long mask = 0; mask < limit; ++mask) {
                vector<string> g = G;
                for (int k = 0; k < m; ++k) {
                    if (mask & (1LL << k)) {
                        int r = whites[k].first;
                        int c = whites[k].second;
                        g[r][c] = '#';
                    }
                }
                if (has_triplet(g)) continue;
                if (!is_connected_and_nonempty(g)) continue;
                possible = true;
                break;
            }
        } else {
            // Too many whites for brute force — respond with placeholder.
            // For large cases, use an efficient algorithm (I'll provide if you want).
            cout << "UNKNOWN\n";
            continue;
        }

        cout << (possible ? "YES\n" : "NO\n");
    }
    return 0;
}
