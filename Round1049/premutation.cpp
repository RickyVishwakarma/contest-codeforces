#include <bits/stdc++.h>
using namespace std;

bool premutate(string& s1 , string& s2){
    // sliding window 
    if(s1.size() > s2.size()) return false;

    vector<int>c1(26 , 0);
    vector<int>c2(26 , 0);
    for(char c : s1){
        c1[c - 'a']++;
    }
    int window  = s1.size();
    for(int i = 0 ; i < window ; i++){
        c2[s2[i] - 'a'];
    }
    if(c1 == c2) return true;
    for(int i = window ; i < s2.size() ; i++){
        c2[s2[i] - 'a']++;
        c2[s2[ i - window] - 'a']--;
        if(c1 == c2) return true;
    }
    return false;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    while (T--) {
        string s1 , s2;
        cin >> s1 >> s2;
        if(premutate(s1 , s2)){
            cout << "YES\n";
        }else{
            cout << "NO\n";
        }
    }
    return 0;
}