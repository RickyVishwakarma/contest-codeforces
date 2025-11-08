#include <bits/stdc++.h>
using namespace std;

// convert integer → 7 lowercase chars
string numToAlpha(long long num) {
    string res;
    for (int i = 0; i < 7; ++i) {
        res.push_back('a' + (num % 26));
        num /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}

// convert 7 lowercase chars → integer
long long alphaToNum(const string &s) {
    long long val = 0;
    for (char c : s)
        val = val * 26 + (c - 'a');
    return val;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string mode;
    cin >> mode;

    if (mode == "first") {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (auto &x : a) cin >> x;

        string encoded = numToAlpha(n);
        for (auto &x : a) encoded += numToAlpha(x);
        cout << encoded << "\n";
    } 
    else {
        string s;
        cin >> s;
        int n = alphaToNum(s.substr(0, 7));
        vector<long long> a;
        a.reserve(n);

        for (int i = 0; i < n; ++i) {
            a.push_back(alphaToNum(s.substr(7 + i * 7, 7)));
        }

        cout << n << "\n";
        for (auto x : a) cout << x << " ";
        cout << "\n";
    }
}
