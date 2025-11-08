// Compile with: g++ -O2 -std=c++17 -march=native -pipe -static -s
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
using vi = vector<int>;
using ll = long long;

struct Query {
    int L, R, lca, idx;
    int u,v;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if(!(cin >> T)) return 0;
    while(T--) {
        int n, k, s, q;
        cin >> n >> k >> s >> q;
        vector<vector<int>> adj(n+1);
        for(int i=0;i<n-1;i++){
            int u,v; cin>>u>>v;
            adj[u].push_back(v); adj[v].push_back(u);
        }

        // colors per node
        vector<vector<int>> colors(n+1);
        for(int i=0;i<s;i++){
            int v,x; cin>>v>>x;
            colors[v].push_back(x);
        }

        // Read queries, store u,v for later
        vector<pair<int,int>> rawQ(q);
        for(int i=0;i<q;i++){
            cin>>rawQ[i].first>>rawQ[i].second;
        }

        // Build iterative Euler tour (enter+exit), depths and parent[0]
        int LOG = 1;
        while((1<<LOG) <= n) LOG++;
        vector<vector<int>> up(LOG, vector<int>(n+1, 0));
        vector<int> depth(n+1, 0);
        vector<int> tin(n+1), tout(n+1);
        vector<int> euler; euler.reserve(2*n+5);
        euler.push_back(0); 
        vector<int> parent(n+1, 0);
        vector<int> itIndex(n+1, 0);
        vector<int> stk;
        stk.reserve(n*2);
        int timer = 0;
        // start at node 1 as root
        stk.push_back(1);
        parent[1] = 1;
        depth[1] = 0;
        // We'll use a manual stack that simulates recursion and produces enter+exit
        vector<int> state(n+1, 0); // 0=not visited, 1=entered
        while(!stk.empty()) {
            int v = stk.back();
            if(state[v] == 0) {
                // enter
                state[v] = 1;
                timer++;
                tin[v] = timer;
                euler.push_back(v);
                // set up parent, depth already set
                up[0][v] = parent[v];
                // push children
                for(int to : adj[v]) {
                    if(to == parent[v]) continue;
                    parent[to] = v;
                    depth[to] = depth[v] + 1;
                    stk.push_back(to);
                }
            } else {
                // exit
                stk.pop_back();
                timer++;
                tout[v] = timer;
                euler.push_back(v);
            }
        }
        int M = (int)euler.size()-1; // euler positions 1..M

        // build binary lifting
        for(int j=1;j<LOG;j++){
            for(int v=1;v<=n;v++){
                up[j][v] = up[j-1][ up[j-1][v] ];
            }
        }
        auto lca = [&](int a, int b){
            if(depth[a] < depth[b]) swap(a,b);
            int diff = depth[a] - depth[b];
            for(int j=0;j<LOG;j++) if(diff & (1<<j)) a = up[j][a];
            if(a==b) return a;
            for(int j=LOG-1;j>=0;j--){
                if(up[j][a] != up[j][b]){
                    a = up[j][a];
                    b = up[j][b];
                }
            }
            return up[0][a];
        };

        // transform queries to Mo on tree format
        vector<Query> queries;
        queries.reserve(q);
        for(int i=0;i<q;i++){
            int u = rawQ[i].first, v = rawQ[i].second;
            if(tin[u] > tin[v]) swap(u,v);
            int w = lca(u,v);
            Query qu;
            qu.idx = i; qu.u = rawQ[i].first; qu.v = rawQ[i].second;
            if(w == u) {
                // contiguous interval [tin[u], tin[v]]
                qu.L = tin[u]; qu.R = tin[v];
                qu.lca = -1;
            } else {
                // interval [tout[u], tin[v]] and lca separate
                qu.L = tout[u]; qu.R = tin[v];
                qu.lca = w;
            }
            queries.push_back(qu);
        }

        // Mo ordering
        int block = max(1, (int)(sqrt(M)));
        sort(queries.begin(), queries.end(), [&](const Query &a, const Query &b){
            int ablock = a.L / block, bblock = b.L / block;
            if(ablock != bblock) return ablock < bblock;
            if((ablock & 1) == 0) return a.R < b.R;
            else return a.R > b.R;
        });

        // counters
        vector<int> cntColor(k+1, 0);           // count of nodes in current window that have color c
        vector<int> freqCount(n+2, 0);         // number of colors that have exactly t occurrences in current window (t index)
        // initially every color has count 0
        freqCount[0] = k;
        vector<char> activeNode(n+1, 0);       // whether node is currently included
        int curL = 1, curR = 0; // current window is empty
        int activeNodes = 0;    // number of nodes currently included (distinct nodes)
        vector<int> ans(q, 0);

        auto add_node = [&](int node){
            // add node's colors
            for(int c : colors[node]) {
                int old = cntColor[c];
                freqCount[old]--;
                cntColor[c] = old + 1;
                freqCount[old+1]++;
            }
            activeNodes++;
        };
        auto remove_node = [&](int node){
            for(int c : colors[node]) {
                int old = cntColor[c];
                freqCount[old]--;
                cntColor[c] = old - 1;
                freqCount[old-1]++;
            }
            activeNodes--;
        };
        auto togglePos = [&](int pos){
            int node = euler[pos];
            if(activeNode[node]){
                // remove
                activeNode[node] = 0;
                remove_node(node);
            } else {
                activeNode[node] = 1;
                add_node(node);
            }
        };

        // process queries with Mo
        for(auto &Qq : queries){
            int L = Qq.L, R = Qq.R;
            while(curL > L) { curL--; togglePos(curL); }
            while(curR < R) { curR++; togglePos(curR); }
            while(curL < L) { togglePos(curL); curL++; }
            while(curR > R) { togglePos(curR); curR--; }

            if(Qq.lca != -1){
                // temporarily toggle lca
                togglePos(tin[Qq.lca]);
                // activeNodes now equals path length
                int pathLen = activeNodes;
                if(pathLen <= n) ans[Qq.idx] = freqCount[pathLen];
                else ans[Qq.idx] = 0;
                // toggle back
                togglePos(tin[Qq.lca]);
            } else {
                int pathLen = activeNodes;
                if(pathLen <= n) ans[Qq.idx] = freqCount[pathLen];
                else ans[Qq.idx] = 0;
            }
        }

        // print answers in input order
        for(int i=0;i<q;i++){
            cout << ans[i] << (i+1==q?'\n':' ');
        }
    }
    return 0;
}
