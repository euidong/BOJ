#include <iostream>
#include <vector>
#include <climits>

using namespace std;


vector<long long> dists;

bool solution(const int N, const int M, const vector<vector<long long>>& edges) {
    dists = vector<long long>(N, LLONG_MAX);
    dists[0] = 0;
    for (int cnt = 0; cnt <= N; ++cnt) {
        for (const auto & edge : edges) {
            if (dists[edge[0]] == LLONG_MAX) continue;
            if (dists[edge[1]] > dists[edge[0]] + edge[2]) {
                if (cnt == N) return true;
                dists[edge[1]] = dists[edge[0]] + edge[2];
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<vector<long long>> edges(M, vector<long long>(3));
    for (int i = 0; i < M; ++i) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--; edges[i][1]--;
    }
    if (solution(N, M, edges)) cout << -1;
    else {
        for (int i = 1; i < N; ++i) {
            const long long dist = dists[i];
            if (dist == LLONG_MAX) cout << -1 << '\n';
            else cout << dist << '\n';
        }
    }
}