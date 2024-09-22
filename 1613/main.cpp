#include <iostream>
#include <vector>

using namespace std;

const int DIST_LIMIT = 401;

vector<vector<int>> solution(const int n, const vector<vector<bool>>& adj)
{
    vector<vector<int>> dists(n, vector<int>(n,DIST_LIMIT));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j) dists[i][j] = 0;
            else if (adj[i][j]) dists[i][j] = 1;
        }
    }

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dists[i][j] > dists[i][k] + dists[k][j])
                    dists[i][j] = dists[i][k] + dists[k][j];
            }
        }
    }

    return dists;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, k; cin >> n >> k;
    vector<vector<bool>> adj(n, vector<bool>(n, false));

    for (int i = 0; i < k; ++i)
    {
        int a, b; cin >> a >> b;
        adj[a-1][b-1] = true;
    }

    const vector<vector<int>> dists = solution(n, adj);

    int s; cin >> s;
    for (int i = 0; i < s; ++i)
    {
        int a, b; cin >> a >> b;
        int output = 0;
        if (dists[a-1][b-1] != DIST_LIMIT) output = -1;
        else if (dists[b-1][a-1] != DIST_LIMIT) output = 1;

        cout << output << '\n';
    }

    return 0;
}