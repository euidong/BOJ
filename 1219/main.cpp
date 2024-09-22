#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long MAX_DIST = 1000000 * 50 * 50 * 2 + 1;
vector<long long> dists;

bool check (const int N, const int D, const int cur, vector<bool>& visited, const vector<vector<long long>>& graph)
{
    visited[cur] = true;
    if (cur == D)
    {
        return true;
    }
    queue<int> q;
    q.push(cur);
    while (!q.empty())
    {
        const int v = q.front();
        q.pop();
        for (int i = 0; i < N; ++i)
        {
            if (visited[i]) continue;
            if (graph[v][i] == -MAX_DIST) continue;
            visited[i] = true;
            if (i == D)
            {
                return true;
            }
            q.push(i);
        }
    }
    return false;
}

bool solution(const int N, const int S, const int D, const vector<vector<long long>>& graph, const int start_point)
{
    dists = vector<long long>(N, -MAX_DIST);
    dists[S] = start_point;

    bool is_pos_infinity = false;
    vector<bool> visited(N, false);

    for (int cnt = 0; cnt <= N; ++cnt)
    {
        for (int cur = 0; cur < N; ++cur)
        {
            for (int next = 0; next < N; ++next)
            {
                if (graph[cur][next] == -MAX_DIST) continue;
                if (dists[cur] == -MAX_DIST) continue;
                if (dists[next] < dists[cur] + graph[cur][next])
                {
                    if (cnt == N)
                    {
                        is_pos_infinity = check(N, D, next, visited, graph);
                        if (is_pos_infinity) return true;
                    }
                    dists[next] = dists[cur] + graph[cur][next];
                }
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, S, D, M; cin >> N >> S >> D >> M;
    vector<vector<long long>> graph(N, vector<long long>(N, -MAX_DIST));
    int stt, dst, prc;
    for (int i = 0; i < M; ++i)
    {
        cin >> stt >> dst >> prc;
        if (graph[stt][dst] < -prc)
            graph[stt][dst] = -prc;
    }
    vector<int> sales(N);
    for (int next = 0; next < N; ++next)
    {
        cin >> sales[next];
        for (int cur = 0; cur < N; ++cur)
        {
            if (graph[cur][next] != -MAX_DIST)
                graph[cur][next] += sales[next];
        }
    }

    const bool is_pos_infinity = solution(N, S, D, graph, sales[S]);

    if (dists[D] == -MAX_DIST) cout << "gg";
    else if (is_pos_infinity) cout << "Gee";
    else cout << dists[D];

    return 0;
}