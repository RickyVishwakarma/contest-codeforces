#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        long long rating, limit, step;
        int rounds;
        cin >> rating >> limit >> step >> rounds;

        string types;
        cin >> types;

        int totalRated = 0;

        for (char roundType : types) {
            if (roundType == '1') {
                // Division 1 → always rated
                totalRated++;
                if (rating >= limit) {
                    rating = max(0LL, rating - step);  // move down if possible
                } else {
                    rating = min(limit - 1, rating + step); // stay below limit
                }
            } else { // Division 2
                if (rating < limit) {
                    totalRated++;
                    rating = min(limit - 1, rating + step);
                }
                // if rating >= limit → unrated, no change
            }
        }

        cout << totalRated << '\n';
    }

    return 0;
}
