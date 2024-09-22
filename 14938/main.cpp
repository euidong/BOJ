#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int DIST_LIMIT = 15 * 100 + 1;

int solution(const int n, const int m, const int r, const vector<int>& items, const vector<vector<int>>& edges)
{
    vector<vector<int>> dists(n, vector<int>(n, DIST_LIMIT));
    for (int i = 0; i < n; ++i) dists[i][i] = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (const auto & edge : edges)
            {
                if (dists[i][edge[0]] == DIST_LIMIT) continue;
                if (dists[i][edge[1]] <= dists[i][edge[0]] + edge[2]) continue;
                dists[i][edge[1]] = dists[i][edge[0]] + edge[2];
            }
        }
    }

    int max_score = 0;
    for (int i = 0; i < n; ++i)
    {
        int score = 0;
        for (int j = 0; j < n; ++j)
        {
            if (dists[i][j] <= m) score += items[j];
        }
        max_score = max(max_score, score);
    }

    return max_score;
}

int main()
{
    int n, m, r; cin >> n >> m >> r;
    vector<int> items(n);
    for (int i = 0; i < n; ++i)
        cin >> items[i];

    vector<vector<int>> edges(2*r, vector<int>(3));
    for (int i = 0; i < r; ++i)
    {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        edges[i][0]--; edges[i][1]--;
        edges[i+r][0] = edges[i][1];
        edges[i+r][1] = edges[i][0];
        edges[i+r][2] = edges[i][2];
    }


    cout << solution(n, m, r, items, edges);

    return 0;
}