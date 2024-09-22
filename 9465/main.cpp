#include <iostream>
#include <vector>

using namespace std;

// cache[x][0] 위아래 둘 다 안먹은 경우
// cache[x][1] 위에만 먹은 경우
// cache[x][2] 아래만 먹은 경우

// cache[x][0] = max(cache[x-1][1], cache[x-1][2])
// cache[x][1] = score[0][x] + max(cache[x-1][2], cache[x-1][0])
// cache[x][2] = score[1][x] + max(cache[x-1][1], cache[x-1][0])

vector<vector<long long>> cache;

long long dp(const int x, const int y, const vector<vector<int>>& scores)
{
    if (cache[x][y] != -1) return cache[x][y];
    if (y == 0) return cache[x][y] = max(dp(x-1, 1, scores), dp(x-1, 2, scores));
    if (y == 1) return cache[x][y] = scores[0][x] + max(dp(x-1, 2, scores), dp(x-1,0, scores));
    return cache[x][y] = scores[1][x] + max(dp(x-1, 1, scores), dp(x-1,0, scores));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    for (int t = 0; t < T; ++t)
    {
        int n; cin >> n;
        cache = vector<vector<long long>>(n, vector<long long>(3, -1));
        vector<vector<int>> scores(2, vector<int>(n));
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                cin >> scores[i][j];
            }
        }
        cache[0][0] = 0;
        cache[0][1] = scores[0][0];
        cache[0][2] = scores[1][0];
        long long max_score = 0;
        for (int i = 0; i < 3; ++i)
            max_score = max(max_score, dp(n-1, i, scores));
        cout << max_score << '\n';
    }
    return 0;
}