#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 마을을 분리할 것임.
// 분리된 마을 안에서 방문 못하는 집이 있어서는 안됨. (즉, 모든 경로는 연결이 가능해야 함.)
// 분리된 마을 간의 도로는 모두 삭제
// 분리된 2개의 마을안에서 MST를 구성해서 가장 짧은 유지비를 획득한다.

// MST를 구축하고, edge를 하나씩 삭제해보면서 가장 짧은 거를 찾기
// 중복된 경로 처리 필요해보임.

// 2 <= N <= 100000
// 1 <= M <= 1000000

int comp(const vector<int>& edge_a, const vector<int>& edge_b)
{
    return edge_a[2] < edge_b[2];
}

int find(vector<int>& parents, const int cur)
{
    if (parents[cur] == cur) return cur;
    return parents[cur] = find(parents, parents[cur]);
}

bool combine(vector<int>& parent, const int a, const int b)
{
    const int root_a = find(parent, a);
    const int root_b = find(parent, b);

    if (root_a == root_b)
        return false;
    parent[root_b] = root_a;
    return true;
}

int kruskal(const int N, const int M, vector<vector<int>>& edges)
{
    vector<int> parents(N);
    for (int i = 0; i < N; ++i) parents[i] = i;

    sort(edges.begin(), edges.end(), comp);

    int tot_dist = 0;
    int max_edge = -1;
    for (const auto & edge : edges)
    {
        if (combine(parents, edge[0], edge[1]))
        {
            tot_dist += edge[2];
            if (max_edge < edge[2])
                max_edge = edge[2];
        }
    }

    return tot_dist - max_edge;
}

int prim(const int N, const int M, vector<vector<int>>& edges)
{
    int start = 0;
    vector<bool> visited(N, false); visited[start] = true;

    vector<vector<vector<int>>> adj_list(N);

    for (const auto edge : edges)
    {
        adj_list[edge[0]].push_back({-edge[2], edge[0], edge[1]});
        adj_list[edge[1]].push_back({-edge[2], edge[1], edge[0]});
    }

    priority_queue<vector<int>> pq;
    for (const auto edge : adj_list[start])
    {
        pq.push(edge);
    }

    int tot_dist = 0;
    int max_dist = -1;

    while (!pq.empty())
    {
        const vector<int> cur = pq.top();
        pq.pop();

        if (visited[cur[2]]) continue;
        visited[cur[2]] = true;
        tot_dist += -cur[0];
        if (max_dist < -cur[0]) max_dist = -cur[0];
        for (const auto & edge : adj_list[cur[2]])
        {
            if (visited[edge[2]]) continue;
            pq.push(edge);
        }
    }

    return tot_dist - max_dist;
}

int solution(const int N, const int M, vector<vector<int>>& edges)
{
    // kruskal's algorithm cause time out.
    return kruskal(N, M, edges);

    // prim's algorithm
    // return prim(N, M, edges);
}


int main() {
    int N, M; cin >> N >> M;
    vector<vector<int>> edges(M);
    int a, b, c;
    for (int i = 0; i < M; ++i)
    {
        cin >> a >> b >> c;
        edges[i] = {a-1, b-1, c};
    }

    cout << solution(N, M, edges);

    return 0;
}