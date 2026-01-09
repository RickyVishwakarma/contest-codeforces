#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        long long n, X, Y;
        cin >> n >> X >> Y;
        string s; 
        cin >> s;
        long long A = 0, B = 0;
        for(char c : s) (c == '4' ? A : B)++;
        
        long long d1   = llabs(X) + llabs(Y);
        long long dInf = max(llabs(X), llabs(Y));
        long long reachMan = A + 2LL * B;
        long long reachInf = A + B;
        bool ok = (d1 <= reachMan) && (dInf <= reachInf);
        cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}

for(char c : s){
    if(c == '4'){
        A++;
    }else{
        B++;
    }
}