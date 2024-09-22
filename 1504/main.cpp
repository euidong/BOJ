#include <iostream>
#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

const int MAX_DIST = 200000 * 1000 + 1;

vector<int> get_the_shortest_dists(const int N, const vector<vector<int>>& graph, const int here) {
    priority_queue<tuple<int, int>> pq;

    vector<int> dists(N, MAX_DIST);
    dists[here] = 0;
    for (int v = 0; v < N; ++v) {
        if (graph[here][v] != -1) {
            dists[v] = graph[here][v];
            pq.push(make_tuple(dists[v], v));
        }
    }

    while (!pq.empty()) {
        tuple<int, int> cur = pq.top();
        pq.pop();
        const int cur_dist = get<0>(cur);
        const int cur_v = get<1>(cur);

        if (cur_dist > dists[cur_v]) continue;

        for (int next_v = 0; next_v < N; ++next_v) {
            if (graph[cur_v][next_v] != -1) {
                if (graph[cur_v][next_v] + dists[cur_v] < dists[next_v]) {
                    dists[next_v] = graph[cur_v][next_v] + dists[cur_v];
                    pq.push(make_tuple(dists[next_v], next_v));
                }
            }
        }
    }

    return dists;
}

int solution(const int N, const int E, const vector<vector<int>>& graph, const int v1, const int v2) {
    // 1. 경로 경우의 수 = 2
    const vector<int> points = {0, v1, v2};
    vector<vector<int>> dists(N);
    for (const auto & point : points)
    {
        dists[point] = get_the_shortest_dists(N, graph, point);
    }
    vector<vector<int>> paths = {{0, v1, v2, N-1}, {0, v2, v1, N-1}};

    vector<int> min_dists(2);

    for (int i = 0; i < paths.size(); ++i) {
        for (int j = 0; j < paths[i].size() - 1; ++j)
        {
            const int dist = dists[paths[i][j]][paths[i][j+1]];

            if (dist == MAX_DIST)
            {
                min_dists[i] = MAX_DIST;
                break;
            };
            min_dists[i] += dist;
        }
    }

    const int min_dist = *min_element(min_dists.begin(), min_dists.end());
    if (min_dist == MAX_DIST) return -1;
    return min_dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, E; cin >> N >> E;
    vector<vector<int>> graph(N, vector<int>(N, MAX_DIST));
    int a, b, c;
    for (int i = 0; i < N; ++i) graph[i][i] = 0;
    for (int e = 0; e < E; e++) {
        cin >> a >> b >> c;
        if (graph[a-1][b-1] > c)
        {
            graph[a-1][b-1] = c;
            graph[b-1][a-1] = c;
        }
    }
    int v1, v2; cin >> v1 >> v2;
    v1--; v2--;

    cout << solution(N, E, graph, v1, v2);


    return 0;
}