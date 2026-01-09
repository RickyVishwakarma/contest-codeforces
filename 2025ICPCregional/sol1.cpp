#include<bits/stdc++.h>
using namespace std;
int main(){
    int g , c , l;
    cin >> g >> c >> l;

    int maxi = max({g , c , l});
    int mini = min({g , c , l});
    if(maxi - mini >= 10){
        cout << "Check again";
    }else{
        vector<int>a = {g, c , l};
        sort(a.begin() , a.end());
        cout << "final " << a[1];
    }
    return 0;
}