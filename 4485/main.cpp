#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

const int INF = 360000;

vector<vector<int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int solution(const int N, const vector<vector<int>>& board)
{
    vector<vector<int>> coins(N, vector<int>(N, INF));
    coins[0][0] = board[0][0];

    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[0][0] = true;

    int y = 0, x = 0;
    for (int i = 0; i < N * N; ++i)
    {
        for (int d = 0; d < 4; ++d)
        {
            const int ny = y + directions[d][0], nx = x + directions[d][1];
            if (ny > -1 && ny < N && nx > -1 && nx < N)
            {
                if (coins[ny][nx] > coins[y][x] + board[ny][nx])
                {
                    coins[ny][nx] = coins[y][x] + board[ny][nx];
                }
            }
        }

        int min_v = INF;
        for (int n = 0; n < N; ++n)
        {
            for (int m = 0; m < N; ++m)
            {
                if (coins[n][m] < min_v && !visited[n][m])
                {
                    min_v = coins[n][m];
                    y = n, x = m;
                }
            }
        }
        visited[y][x] = true;
    }

    return coins[N-1][N-1];
}

int main()
{
    ios_base::sync_with_stdio(false);

    int t = 1;
    while (true)
    {
        int N; cin >> N;
        if (N == 0) break;
        vector<vector<int>> board(N, vector<int>(N));
        for (int n1 = 0; n1 < N; ++n1) for (int n2 = 0; n2 < N; ++n2) cin >> board[n1][n2];

        cout << "Problem " << t++ << ": " << solution(N, board) << '\n';
    }
    return 0;
}