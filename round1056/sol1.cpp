#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;

    while (testCases--) {
        int teams;
        cin >> teams;

        int totalMatches = (teams * 2) - 2;
        cout << totalMatches << '\n';
    }

    return 0;
}
