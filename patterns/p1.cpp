#include<bits/stdc++.h>
using namespace std;

// This is the code of the pyramid printing 

int main(){
    int n;
    cout << "Enter a number : "; 
    cin >> n;
    for(int i = 1 ; i <= n ; i++){
        // for the space 
        for(int j =  1 ; j <=  n - i ; j++) cout << " ";
        //  for the stars
        for(int k = 1 ; k < 2*i - 1 ; k++) cout << "*";
        cout << endl;
    }
    return 0;
}