#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DIST_LIMIT = 100000 * 999 + 1;

int solution(const int N, const int M, const vector<vector<int>>& buses, const int src, const int dst) {
    vector<int> dists(N, DIST_LIMIT);
    dists[src] = 0;

    vector<vector<int>> adj(N, vector<int>(N, DIST_LIMIT));
    for (const vector<int>& bus : buses) {
        if (adj[bus[0]][bus[1]] > bus[2]) {
            adj[bus[0]][bus[1]] = bus[2];
        }
    }

    priority_queue<vector<int>> pq;
    for (int i = 0; i < N; ++i) {
        if (adj[src][i] != DIST_LIMIT) {
            pq.push({-adj[src][i], i});
            dists[i] = adj[src][i];
        }
    }

    while (!pq.empty()) {
        vector<int> cur = pq.top();
        pq.pop();
        const int cur_dist = -cur[0];
        const int cur_loc = cur[1];

        if (dists[cur_loc] < cur_dist) continue;
        for (int next_loc = 0; next_loc < N; ++next_loc) {
            if (dists[next_loc] > adj[cur_loc][next_loc] + dists[cur_loc]) {
                dists[next_loc] = adj[cur_loc][next_loc] + dists[cur_loc];
                pq.push({-dists[next_loc], next_loc});
            }
        }
    }

    return dists[dst];
}

int main() {
    int N, M; cin >> N >> M;
    vector<vector<int>> buses(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        cin >> buses[i][0] >> buses[i][1] >> buses[i][2];
        buses[i][0]--; buses[i][1]--;
    }
    int src, dst; cin >> src >> dst;

    cout << solution(N, M, buses, src-1, dst-1);

    return 0;
}