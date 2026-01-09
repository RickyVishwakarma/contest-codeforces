#include <bits/stdc++.h>
using namespace std;

struct Route {
    long long a, b;
    double score;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    long long L, busSpeed, walkSpeed;
    cin >> N >> M >> L >> busSpeed >> walkSpeed;

    vector<Route> lines(N);
    for (int i = 0; i < N; i++) {
        long long s, t;
        cin >> s >> t;

        double ride = (double)(t - s) / busSpeed;
        double walk = (double)(L - t) / walkSpeed;

        lines[i] = {s, t, ride + walk};
    }

    // people data
    vector<pair<long long,int>> persons(M);
    for (int i = 0; i < M; i++) {
        long long p;
        cin >> p;
        persons[i] = {p, i};
    }

    sort(lines.begin(), lines.end(),
         [](const Route &r1, const Route &r2){
             return r1.a < r2.a;
         });

    sort(persons.begin(), persons.end());

    // min-heap: {best_time, end_point}
    priority_queue<
        pair<double,long long>,
        vector<pair<double,long long>>,
        greater<pair<double,long long>>
    > bag;

    vector<double> out(M);
    int ptr = 0;

    for (auto &pp : persons) {

        long long pos = pp.first;
        int id = pp.second;

        // insert all buses that start before we reach 'pos'
        while (ptr < N && lines[ptr].a <= pos) {
            bag.push({lines[ptr].score, lines[ptr].b});
            ptr++;
        }

        // remove expired buses
        while (!bag.empty() && bag.top().second < pos) {
            bag.pop();
        }

        // fallback: just walk
        double answer = (double)(L - pos) / walkSpeed;

        // check if some active bus is usable
        if (!bag.empty()) {
            answer = min(answer, bag.top().first);
        }

        out[id] = answer;
    }

    cout << fixed << setprecision(10);
    for (double v : out) {
        cout << v << "\n";
    }

    return 0;
}
