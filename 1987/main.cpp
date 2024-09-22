#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> deltas = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int dfs(const int y, const int x, const int R, const int C, const vector<vector<char>>& board, vector<bool>& visited)
{
    int max_path = 1;
    for (const auto & delta : deltas)
    {
        const int ny = y + delta[0], nx = x + delta[1];
        if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
        if (visited[board[ny][nx] - 'A']) continue;
        visited[board[ny][nx] - 'A'] = true;
        max_path = max(max_path, dfs(ny, nx, R, C, board, visited) + 1);
        visited[board[ny][nx] - 'A'] = false;
    }
    return max_path;
}

int solution(const int R, const int C, const vector<vector<char>>& board)
{
    vector<bool> visited(26, false);
    visited[board[0][0] - 'A'] = true;

    return dfs(0, 0, R, C, board, visited);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int R, C; cin >> R >> C;
    vector<vector<char>> board(R, vector<char>(C));
    for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> board[i][j];

    cout << solution(R, C, board);
    return 0;
}