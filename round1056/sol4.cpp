#include <bits/stdc++.h>
using namespace std;

// Simulated interactor: mark which batteries are working
bool isWorking(int id, vector<int>& working) {
    return find(working.begin(), working.end(), id) != working.end();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        // ---- Simulation part ----
        // (you can change which batteries work here)
        vector<int> working;  
        if (n == 3) working = {2, 3};
        else if (n == 10) working = {1, 4, 6, 9};
        else working = {1, 2};

        bool found = false;

        for (int i = 1; i <= n && !found; ++i) {
            for (int j = i + 1; j <= n && !found; ++j) {
                cout << "Testing " << i << " " << j << " → ";

                int x = (isWorking(i, working) && isWorking(j, working)) ? 1 : 0;
                cout << x << "\n";

                if (x == 1) {
                    cout << "✅ Found working pair: " << i << " " << j << "\n\n";
                    found = true;
                }
            }
        }
        if (!found) cout << "❌ No working pair found (something wrong)\n\n";
    }

    return 0;
}
