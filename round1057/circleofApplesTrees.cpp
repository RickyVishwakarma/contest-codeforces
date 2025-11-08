#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int n;
        cin >> n;

        vector<int> beautyValues(n);
        for (int &val : beautyValues)
            cin >> val;


        set<int> uniqueBeauties;
        for (int val : beautyValues)
            uniqueBeauties.insert(val);

        cout << uniqueBeauties.size() << '\n';
    }

    return 0;
}
