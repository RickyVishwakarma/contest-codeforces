#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

struct NezukoSolver {
   
    static int64 minTurns(int64 h, int64 d) {
        if (h == 1) {
         
            return 2 * d;
        }
        if (h == 2 || h == 3) {
            
            return 2 * d - 1;
        }
        
        return d + (d - 1) / 2;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long h, d;
        cin >> h >> d;
        cout << NezukoSolver::minTurns(h, d) << "\n";
    }
    return 0;
}
