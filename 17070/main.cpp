#include <iostream>
#include <vector>

using namespace std;

// cache[i][j][0] = 오른쪽 끝이 i,j에 가로로 도착한 경우
// cache[i][j][1] = 오른쪽 끝이 i,j에 대각선으로 도착한 경우
// cache[i][j][2] = 오른쪽 끝이 i,j에 세로로 도착한 경우

// cache[i][j][0] = cache[i][j-1][0] + cache[i][j-1][1];
// cache[i][j][1] = cache[i-1][j-1][0] + cahce[i-1][j-1][1] + cache[i-1][j-1][2];
// cache[i][j][2] = cache[i-1][j][1] + cache[i-1][j][2];

vector<vector<vector<int>>> cache;
vector<vector<int>> board;

int dp(const int y, const int x, const int k)
{
    if (cache[y][x][k] != -1) return cache[y][x][k];

    if (board[y][x] == 1) return cache[y][x][k] = 0;

    if (k == 0)
        return cache[y][x][k] = dp(y, x-1, 0) + dp(y, x-1, 1);
    if (k == 2)
        return cache[y][x][k] = dp(y-1, x, 1) + dp(y-1, x, 2);
    if (board[y-1][x] == 1 || board[y][x-1] == 1 || board[y-1][x-1] == 1)
        return cache[y][x][k] = 0;
    return cache[y][x][k] = dp(y-1, x-1,0) + dp(y-1, x-1, 1) + dp(y-1, x-1, 2);
}


int solution(const int N)
{
    return dp(N-1, N-1, 0) + dp(N-1, N-1, 1) + dp(N-1, N-1, 2);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin >> N;

    cache = vector<vector<vector<int>>>(N, vector<vector<int>>(N, vector<int>(3, -1)));
    board = vector<vector<int>>(N, vector<int>(N));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> board[i][j];


    cache[0][0][0] = cache[0][0][1] = cache[0][0][2] = 0;

    bool has_wall = false;
    for (int i = 1; i < N; ++i)
    {
        cache[i][0][0] = cache[i][0][1] = cache[i][0][2] = 0;
        cache[0][i][1] = cache[0][i][2] = 0;
        if (board[0][i] == 1) has_wall = true;
        cache[0][i][0] = has_wall ? 0 : 1;
    }

    cout << solution(N);
    return 0;
}