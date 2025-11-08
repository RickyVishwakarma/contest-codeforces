#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n;
        string s; cin >> n >> s;
        while((int)s.size() < n){
            string temp;
            if(!(cin >> temp))break;
            s += temp;
        }
        if((int)s.size() > n) s =  s.substr(0, n);
        bool sorted = true;
        for(int i = 1 ; i < n ; i++) if (s[i] < s[i-1]){sorted = false; break;}
        if (sorted){cout << 0 << endl ; continue;}
        int blocks = 0; 
        for(int i = 1 ; i < n ; i++) if(s[i] == '1' && s[i+1] == '0') blocks++;
        if(blocks == 1) cout << 1 << endl;
        else cout << 2 << endl;
    }
    return 0;
}
