#include <iostream>
#include <vector>
#include <climits>

using namespace std;



string solution(const int N, const int M, const int W, const vector<vector<int>>& edges) {
    auto dists = vector<int>(N, 0);

    for (int cnt = 0; cnt <= N; ++cnt) {
        for (const auto & edge : edges)
        {
            const int cur = edge[0], next = edge[1], cost = edge[2];
            if (dists[next] > dists[cur] + cost) {
                dists[next] = dists[cur] + cost;
                if (cnt == N) return "YES";
            }
        }
    }

    return "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int TC; cin >> TC;
    for (int tc = 0; tc < TC; ++tc) {
        int N, M, W; cin >> N >> M >> W;
        vector<vector<int>> edges;
        int S, E, T;
        for (int m = 0; m < M; ++m) {
            cin >> S >> E >> T;
            edges.push_back({S-1, E-1, T});
            edges.push_back({E-1, S-1, T});
        }
        for (int w = 0; w < W; ++w) {
            cin >> S >> E >> T;
            edges.push_back({S-1, E-1, -T});
        }
        cout << solution(N, M, W, edges) << '\n';
    }
    return 0;
}
