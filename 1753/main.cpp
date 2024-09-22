#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int DIST_LIMIT = 20000 * 10;

vector<vector<vector<int>>> adj;

int dists[20000];

void solution(const int V, const int E, const int S) {
    for (int i = 0; i < V; ++i) dists[i] = DIST_LIMIT;

    priority_queue<pair<int, int>> pq;
    dists[S] = 0;
    pq.push(make_pair(0, S));

    while (!pq.empty()) {
        const pair<int, int> cur = pq.top();
        pq.pop();
        const int cur_dist = -cur.first;
        const int cur_loc = cur.second;
        if (dists[cur_loc] < cur_dist) continue;
        for (const auto & edge : adj[cur_loc]) {
            const int next_loc = edge[0];
            const int next_dist = edge[1];
            if (dists[next_loc] <= dists[cur_loc] + next_dist) continue;
            dists[next_loc] = dists[cur_loc] + next_dist;
            pq.push(make_pair(-dists[next_loc], next_loc));
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E, S; cin >> V >> E >> S;

    // 인접 행렬이 아닌 인접 리스트로 해야 풀 수 있음.
    adj = vector<vector<vector<int>>>(20000);
    int u,v;
    short w;
    for (int i = 0; i < E; ++i) {
        cin >> u >> v >> w;
        adj[u-1].push_back({v-1, w});
    }
    solution(V, E, S-1);
    
    for (int i = 0; i < V; ++i) {
        if (dists[i] == DIST_LIMIT)
            cout << "INF\n";
        else
            cout << dists[i] << '\n';
    }

    return 0;
}