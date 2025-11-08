#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        string sorted = s;
        sort(sorted.begin(), sorted.end());
        if (s == sorted) {
            cout << 0 << "\n";
            continue;
        }
        int first1 = s.find('1');
        int last0 = s.rfind('0');
        bool alreadySortedInside = true;
        for (int i = first1; i <= last0; i++) {
            if (s[i] == '0') {
                alreadySortedInside = false;
                break;
            }
        }
        if (alreadySortedInside) {
            cout << 1 << "\n";
        } else {
            cout << 2 << "\n";
        }
    }
    return 0;
}
