#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int comp(vector<int> a, vector<int> b)
{
    return a[2] < b[2];
}

int find(const vector<int>& parents, const int a)
{
    if (parents[a] == a) return a;
    return find(parents, parents[a]);
}

bool combine(vector<int>& parents, const int a, const int b) {
    const int root_a = find(parents, a);
    const int root_b = find(parents, b);
    if (root_a == root_b) return false;
    parents[root_b] = root_a;
    return true;
}

int kruskal(const int N, const int M, vector<vector<int>>& edges)
{
    sort(edges.begin(), edges.end(), comp);
    vector<int> parents(N, -1);
    for (int i = 0; i < N; ++i) parents[i] = i;

    int dist = 0;
    int cnt = 0;

    for (const auto & edge : edges)
    {
        if (combine(parents, edge[0], edge[1]))
        {
            dist += edge[2];
            cnt++;
            if (cnt == N-1) break;
        }
    }

    return dist;
}

int prim(const int N, const int M, vector<vector<int>>& edges)
{
    vector<vector<vector<int>>> adj_list(N);
    for (const auto & edge : edges)
    {
        adj_list[edge[0]].push_back({-edge[2], edge[0], edge[1]});
        adj_list[edge[1]].push_back({-edge[2], edge[1], edge[0]});
    }



    vector<bool> visited(N, false);
    visited[0] = true;

    priority_queue<vector<int>> pq;
    for (const auto & edge : adj_list[0])
        pq.push(edge);

    int dist = 0;
    while(!pq.empty())
    {
        const vector<int> cur_edge = pq.top();
        pq.pop();

        if (visited[cur_edge[2]]) continue;
        dist += -cur_edge[0];
        visited[cur_edge[2]] = true;
        for (const auto & edge : adj_list[cur_edge[2]])
        {
            if (visited[edge[2]]) continue;
            pq.push(edge);
        }
    }
    return dist;
}

int solution(const int N, const int M, vector<vector<int>>& edges)
{
    // kruskal
    return kruskal(N, M, edges);

    // prim
    // return prim(N, M, edges);
}

int main()
{
    int N; cin >> N;
    int M; cin >> M;
    vector<vector<int>> edges(M, vector<int>(3));
    int a, b, c;
    for (int i = 0; i < M; ++i)
    {
        cin >> a >> b >> c;
        edges[i] = {a-1, b-1, c};
    }

    cout << solution(N, M, edges);
    return 0;
}