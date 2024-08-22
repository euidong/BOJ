#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int NOT_EXIST = (5200 * 1000 + 1);

string solution(const int N, const int M, const int W, vector<vector<int>>& roads, vector<vector<int>>& wormholes) {
    vector<vector<int>> dist_matrix(N+1, vector<int>(N+1, NOT_EXIST));

    vector<vector<int>> edges;

    for (const auto & road : roads) {
        edges.push_back({ road[0], road[1], road[2] });
        edges.push_back({ road[1], road[0], road[2] });
    }
    for (const auto & wormhole : wormholes) {
        edges.push_back({wormhole[0], wormhole[1], -wormhole[2]});
    }

    vector<bool> visited(N+1, false);
    for (int start_v = 1; start_v <= N; ++start_v) {
        dist_matrix[start_v][start_v] = 0;
        if (visited[start_v]) continue;
        visited[start_v] = true;
        for (int v = 1; v <= N; ++v) {
            for (const auto & edge : edges) {
                const int cur_v = edge[0], next_v = edge[1], cost = edge[2];
                if (dist_matrix[start_v][cur_v] != NOT_EXIST && dist_matrix[start_v][next_v] > dist_matrix[start_v][cur_v] + cost) {
                    dist_matrix[start_v][next_v] = dist_matrix[start_v][cur_v] + cost;
                    visited[next_v] = true;
                    if (v == N) return "YES";
                }
            }
        }
    }

    return "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int TC; cin >> TC;
    for (int tc = 0; tc < TC; tc++) {
        int N, M, W; cin >> N >> M >> W;
        vector<vector<int>> roads(M, vector<int>(3));
        for (int m = 0; m < M; ++m) for (int i = 0; i < 3; ++i) cin >> roads[m][i];
        vector<vector<int>> wormholes(W, vector<int>(3));
        for (int w = 0; w < W; ++w) for (int i = 0; i < 3; ++i) cin >> wormholes[w][i];
        cout << solution(N, M, W, roads, wormholes) << '\n';
    }

    return 0;
}