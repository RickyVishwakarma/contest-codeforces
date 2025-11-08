#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;
    while(T--){
        int len, gap;
        string bin;
        cin >> len >> gap >> bin;

        int safe = 0;
        int prev = -1e9;

        for(int idx = 0; idx < len; ++idx){
            char bit = bin[idx];
            if(bit == '1'){
                if(idx - prev >= gap){
       
                    ++safe;
                    prev = idx;
                } else {
            
                    prev = idx;
                }
            }
        }
        cout << safe << '\n';
    }
}
