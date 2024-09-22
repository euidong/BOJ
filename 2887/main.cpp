#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int comp_x(const vector<int>& a, const vector<int>& b)
{
    return a[0] < b[0];
}

int comp_y(const vector<int>& a, const vector<int>& b)
{
    return a[1] < b[1];
}

int comp_z(const vector<int>& a, const vector<int>& b)
{
    return a[2] < b[2];
}

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

long long solution(const int N, vector<vector<int>>& plants)
{
    for (int i = 0; i < N; ++i)
        plants[i].push_back(i); // plant id 할당 및 삽입

    vector<vector<int>> edges;
    auto comps = {comp_x, comp_y, comp_z};

    for (int i = 0; i < 3; ++i)
    {
        sort(plants.begin(), plants.end(), *(comps.begin() + i));
        for (int j = 1; j < N; ++j)
        {
            edges.push_back({plants[j-1][3], plants[j][3], abs(plants[j][i] - plants[j-1][i])});
        }
    }

    sort(edges.begin(), edges.end(), comp_z); // edges.size = 3*N <= 300,000

    vector<int> parents(N);
    for (int i = 0; i < N; ++i) parents[i] = i;

    long long cost = 0;

    for (const auto & edge : edges)
    {
        if (combine(parents, edge[0], edge[1]))
        {
            cost += edge[2];
        }
    }

    return cost;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<vector<int>> plants(N, vector<int>(3));
    for(int i = 0; i < N; ++i) for(int j = 0; j < 3; ++j) cin >> plants[i][j];

    cout << solution(N, plants);

    return 0;
}