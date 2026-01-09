#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void execute_logic() {
    int n;
    if (!(cin >> n)) return;

    vector<int> location(n + 1);
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        location[val] = i; 
    }

    ll best_payout = 0;

    for (int start_val = 1; start_val <= n; ++start_val) {
        int internal_inversions = 0;
        
        for (int end_val = start_val; end_val <= n; ++end_val) {
            int penalty = 0;
            for (int prev = start_val; prev < end_val; ++prev) {
                if (location[prev] > location[end_val]) {
                    penalty++;
                }
            }
            
            internal_inversions += penalty;
            
            int sequence_len = (end_val - start_val + 1);
            ll current_score = (ll)sequence_len - internal_inversions;
            
            if (current_score > best_payout) {
                best_payout = current_score;
            }
        }
    }

    cout << best_payout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int test_cases;
    if (!(cin >> test_cases)) return 0;
    
    while (test_cases--) {
        execute_logic();
    }
    
    return 0;
}