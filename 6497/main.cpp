#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int find(vector<int>& parents, const int cur)
{
    if (parents[cur] == cur) return cur;
    return parents[cur] = find(parents, parents[cur]);
}

bool combine(vector<int>& parents, const int a, const int b)
{
    const int root_a = find(parents, a);
    const int root_b = find(parents, b);
    if (root_a == root_b) return false;
    parents[root_a] = root_b;
    return true;
}

bool comp(const vector<int>& a, const vector<int>& b)
{
    return a[2] < b[2];
}

int solution(const int m, const int n, vector<vector<int>>& edges)
{
    vector<int> parents(m);
    for(int i = 0; i < m; ++i) parents[i] = i;
    sort(edges.begin(), edges.end(), comp);

    int cost = 0;
    for (const auto & edge : edges)
    {
        if (!combine(parents, edge[0], edge[1]))
        {
            cost += edge[2];
        }
    }
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    while (true)
    {
        int m, n; cin >> m >> n;
        if (m == 0 && n == 0) break;

        vector<vector<int>> edges(n, vector<int>(3));

        for (int i = 0; i < n; ++i)
            cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

        cout << solution(m, n, edges) << '\n';
    }

    return 0;
}