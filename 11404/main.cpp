#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int DIST_LIMIT = 100000 * 100000 + 1;

void solution(const int n, const int m, const vector<vector<int>>& buses)
{
    vector<vector<long long>> dists(n, vector<long long>(n, DIST_LIMIT));
    for (int i = 0; i < n; ++i)
        dists[i][i] = 0;

    for (const auto & bus: buses)
        if (dists[bus[0]][bus[1]] > bus[2])
            dists[bus[0]][bus[1]] = bus[2];

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

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (dists[i][j] == DIST_LIMIT) dists[i][j] = 0;
            cout << dists[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n, m; cin >> n >> m;
    vector<vector<int>> buses;
    int a, b, c;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> c;
        buses.push_back({a-1, b-1, c});
    }

    solution(n, m, buses);
    return 0;
}