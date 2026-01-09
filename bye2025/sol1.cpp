#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;cin >> t;
    while(t--){
        string s ;cin >> s;
        bool flag = false;
        for(char c : s){
            if(c == 'N'){
                flag = true;
                break;
            }
        }
        if(flag) cout << "YES\n";
        else cout << "NO\n";
    }

    

    return 0;
}