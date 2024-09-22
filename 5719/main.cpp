#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int MAX_DIST = 1000 * 10000 + 1;

int dijkstra(const int N, const int S, const int D, vector<vector<int>>& graph)
{
    vector<vector<int>> parents(N);
    priority_queue<vector<int>> pq;
    vector<int> dists(N, MAX_DIST);
    dists[S] = 0;
    for (int i = 0; i < N; ++i)
    {
        if (i == S) continue;
        if (graph[S][i] != -1)
        {
            dists[i] = graph[S][i];
            pq.push({ -graph[S][i], i });
            parents[i] = {S};
        }
    }

    vector<bool> visited(N, false);
    visited[S] = true;

    while (!pq.empty())
    {
        vector<int> cur = pq.top();
        pq.pop();
        const int cur_dist = -cur[0];
        const int cur_loc = cur[1];

        if (dists[cur_loc] < cur_dist) continue;
        visited[cur_loc] = true;
        for (int next_loc = 0; next_loc < N; ++next_loc)
        {
            if (visited[next_loc]) continue;
            if (graph[cur_loc][next_loc] == -1) continue;
            if (dists[next_loc] > dists[cur_loc] + graph[cur_loc][next_loc])
            {
                dists[next_loc] = dists[cur_loc] + graph[cur_loc][next_loc];
                parents[next_loc] = {cur_loc};
                pq.push({-dists[next_loc], next_loc});
            } else if (dists[next_loc] == dists[cur_loc] + graph[cur_loc][next_loc])
            {
                parents[next_loc].push_back(cur_loc);
            }
        }
    }

    queue<vector<int>> q;
    for (const auto & parent : parents[D])
        q.push({parent, D});
    while (!q.empty())
    {
        const vector<int> road = q.front();
        q.pop();
        graph[road[0]][road[1]] = -1;
        if (road[0] == S) continue;
        for (const auto & parent : parents[road[0]])
            q.push({parent, road[0]});
    }

    return dists[D];
}


int solution(const int N, const int M, const int S, const int D, vector<vector<int>>& graph)
{
    // 반복.
        // 1. "최단 거리"보다 작은 최단 경로 찾기
        // 2. 같거나 작다면 삭제 및 "최단 거리" 갱신
            // 최단 경로로 가는 방법이 여러 개인 경우 처리 방안이 필요
            // ex. 0 -(1)-> 1 -(1)-> 2
            // ex. 0 -(2)-> 2
        // 3. 아니라면 MAX만 갱신하고 종료

    if (MAX_DIST == dijkstra(N, S, D, graph))
        return -1;
    const int dist = dijkstra(N, S, D, graph);
    if (dist == MAX_DIST) return -1;
    return dist;
}


int dijkstra_v2(const int N, const int S, const int D, const vector<vector<int>>& graph)
{
    priority_queue<vector<int>> pq;
    vector<int> dists(N, MAX_DIST);
    dists[S] = 0;
    for (int i = 0; i < N; ++i)
    {
        if (i == S) continue;
        if (graph[S][i] != -1)
        {
            dists[i] = graph[S][i];
            pq.push({ -graph[S][i], i });
        }
    }

    while (!pq.empty())
    {
        vector<int> cur = pq.top();
        pq.pop();
        const int cur_dist = -cur[0];
        const int cur_loc = cur[1];

        if (dists[cur_loc] < cur_dist) continue;
        for (int next_loc = 0; next_loc < N; ++next_loc)
        {
            if (graph[cur_loc][next_loc] == -1) continue;
            if (dists[next_loc] > dists[cur_loc] + graph[cur_loc][next_loc])
            {
                dists[next_loc] = dists[cur_loc] + graph[cur_loc][next_loc];
                pq.push({-dists[next_loc], next_loc});
            }
        }
    }

    return dists[D];
}

set<vector<int>> edges_being_removed;
vector<int> dists;
vector<int> min_point_dists;

void dfs(const int N, const int cur, const int dst, const int min_dist, const vector<vector<int>>& graph, const int acc, vector<vector<int>>& path)
{
    if (cur == dst)
    {
        if (min_dist == acc)
        {
            int dist = 0;
            for (const auto & edge : path)
            {
                edges_being_removed.insert(edge);
                dist += graph[edge[0]][edge[1]];
                min_point_dists[edge[1]] = dist;
            }
        }
        return;
    }
    for (int next = 0; next < N; ++next)
    {
        if (graph[cur][next] == -1) continue;
        const int next_dist = acc + graph[cur][next];
        if (next_dist <= min_dist)
        {
            if (dists[next] > next_dist)
            {
                dists[next] = next_dist;
                path.push_back({cur, next});
                dfs(N, next, dst, min_dist, graph, next_dist, path);
                path.pop_back();
            } else if (dists[next] == next_dist && dists[next] == min_point_dists[next])
            {
                int dist = 0;
                path.push_back({cur, next});
                for (const auto & edge : path)
                {
                    edges_being_removed.insert(edge);
                    dist += graph[edge[0]][edge[1]];
                    min_point_dists[edge[1]] = dist;
                }
                path.pop_back();
            }

        }
    }
}

int solution_v2(const int N, const int M, const int S, const int D, vector<vector<int>>& graph)
{
    // 반복.
    // 1. 최단 거리 구하기
    // 2. DFS로 최단 거리 경로 모두 삭제.
    // 3. 최단 거리 구하고 return
    int min_dist = dijkstra_v2(N, S, D, graph);
    if (min_dist == MAX_DIST) return -1;

    // 가장 짧은 거리를 삭제함.
    vector<vector<int>> path;
    edges_being_removed.clear();
    dists = vector<int>(N, MAX_DIST);
    min_point_dists = vector<int>(N, MAX_DIST);
    dfs(N, S, D, min_dist, graph, 0, path);

    for (const auto & edge : edges_being_removed)
        graph[edge[0]][edge[1]] = -1;

    min_dist = dijkstra_v2(N, S, D, graph);
    if (min_dist == MAX_DIST) return -1;
    return min_dist;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    while (true)
    {
        int N, M; cin >> N >> M;
        if (N == 0 && M == 0) break;
        int S, D; cin >> S >> D;
        vector<vector<int>> graph(N, vector<int>(N, -1));
        for (int i = 0; i < M; ++i)
        {
            int U, V, P; cin >> U >> V >> P;
            graph[U][V] = P;
        }
        cout << solution_v2(N, M, S, D, graph) << '\n';
    }
    return 0;
}