#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        string result;
        vector<int> lowercase, uppercase;

        for (int i = 0; i < (int)s.size(); i++) {
            char c = s[i];
            if (c == 'b') {
                if (!lowercase.empty()) {
                    int idx = lowercase.back();
                    lowercase.pop_back();
                    result[idx] = '#'; 
                }
            } else if (c == 'B') {
                if (!uppercase.empty()) {
                    int idx = uppercase.back();
                    uppercase.pop_back();
                    result[idx] = '#'; 
                }
            } else {
                result.push_back(c);
                if (islower(c)) lowercase.push_back((int)result.size() - 1);
                else uppercase.push_back((int)result.size() - 1);
            }
        }
        for (char c : result) {
            if (c != '#') cout << c;
        }
        cout << "\n";
    }

    return 0;
}
