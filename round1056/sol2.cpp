#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

/*
  Long / clear solution for "Abraham's Great Escape".
  Key observations:
    - Let t = n*n - k be number of non-escaping (trapped) cells.
    - t must be even (we will form 2-cell cycles / dominoes).
    - To avoid any other cell accidentally pointing into a cycle,
      we ensure all cycle cells are placed as the "last" cells in a
      row-major ordering. Then we assign arrows for earlier cells
      so they only ever point to earlier cells or to the outside.
      Thus no earlier cell can point into a later (cycle) cell.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int n, k;
        cin >> n >> k;

        int total = n * n;
        int trapped = total - k;

        // feasibility: trapped must be even
        if (trapped < 0 || (trapped & 1)) {
            cout << "NO\n";
            continue;
        }

        int pairsNeeded = trapped / 2; // number of 2-cell cycles required

        vector<pair<pair<int,int>, pair<int,int>>> dominoes;
        dominoes.reserve((n * n) / 2);

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c + 1 < n; c += 2) {
                dominoes.push_back({{r, c}, {r, c + 1}});
            }
        }
        if (n % 2 == 1) {

            int lastc = n - 1;
            for (int r = 0; r + 1 < n; r += 2) {
                dominoes.push_back({{r, lastc}, {r + 1, lastc}});
            }
        }


        if (pairsNeeded > (int)dominoes.size()) {
            cout << "NO\n";
            continue;
        }

       
        int totalDom = (int)dominoes.size();
        int startIdx = totalDom - pairsNeeded; 
        vector<string> grid(n, string(n, 'U'));

   
        for (int idx = startIdx; idx < totalDom; ++idx) {
            auto p = dominoes[idx].first;
            auto q = dominoes[idx].second;
            int r1 = p.first, c1 = p.second;
            int r2 = q.first, c2 = q.second;

            if (r1 == r2) {
                
                if (c1 < c2) {
                    grid[r1][c1] = 'R';
                    grid[r2][c2] = 'L';
                } else {
                    grid[r2][c2] = 'R';
                    grid[r1][c1] = 'L';
                }
            } else {
                
                if (r1 < r2) {
                    grid[r1][c1] = 'D';
                    grid[r2][c2] = 'U';
                } else {
                    grid[r2][c2] = 'D';
                    grid[r1][c1] = 'U';
                }
            }
        }


        cout << "YES\n";
        for (int r = 0; r < n; ++r) {
            cout << grid[r] << '\n';
        }
    }

    return 0;
}
