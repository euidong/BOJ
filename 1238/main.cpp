#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_DIST = 1000 * 10000 + 1;

vector<int> get_dists(const int N, const int M, const vector<vector<int>>& graph, const int here)
{
    vector<int> dists(N, MAX_DIST);
    dists[here] = 0;

    priority_queue<vector<int>> pq;

    for (int next = 0; next < N; ++next)
    {
        if (graph[here][next] == -1) continue;
        dists[next] = graph[here][next];
        pq.push({dists[next], next});
    }

    while (!pq.empty())
    {
        vector<int> cur = pq.top();
        pq.pop();
        const int cur_dist = cur[0], cur_n = cur[1];
        if (cur_dist > dists[cur_n]) continue;

        for (int next = 0; next < N; ++next)
        {
            if (graph[cur_n][next] == -1) continue;
            if (dists[cur_n] + graph[cur_n][next] >= dists[next]) continue;
            dists[next] = dists[cur_n] + graph[cur_n][next];
            pq.push({dists[next], next});
        }
    }

    return dists;
}

int solution(const int N, const int M, const int X, const vector<vector<int>>& graph)
{
    vector<vector<int>> dists(2, vector<int>(N));
    dists[0] = get_dists(N, M, graph, X);
    vector<vector<int>> reverse_graph(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) reverse_graph[i][j] = graph[j][i];
    dists[1] = get_dists(N, M, reverse_graph, X);

    vector<int> round_trip_time(N, 0);
    for (int start = 0; start < N; ++start)
    {
        round_trip_time[start] = dists[1][start] + dists[0][start];
    }

    return *max_element(round_trip_time.begin(), round_trip_time.end());
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M, X; cin >> N >> M >> X;
    vector<vector<int>> graph(N, vector<int>(N, -1));
    int st, ed, dt;
    for (int m = 0; m < M; ++m)
    {
        cin >> st >> ed >> dt;
        graph[st-1][ed-1] = dt;
    }

    cout << solution(N, M, X - 1, graph);

    return 0;
}