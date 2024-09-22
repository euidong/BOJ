#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> deltas = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs(const int N, const int M, const int y, const int x, vector<vector<int>>& board, vector<vector<bool>>& visited)
{
    for (const auto& delta : deltas)
    {
        const int ny = y + delta[0], nx = x + delta[1];
        if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
        if (board[ny][nx] != 1 && !visited[ny][nx])
        {
            board[ny][nx] = 2;
            visited[ny][nx] = true;
            dfs(N, M, ny, nx, board, visited);
        }
    }
}

int remove_cheese(const int N, const int M, vector<vector<int>>& board)
{
    int cnt = 0;
    vector<vector<int>> new_board = board;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (board[i][j] != 1) continue;
            int air_cnt = 0;
            for (const auto& delta : deltas)
            {
                const int ni = i + delta[0], nj = j + delta[1];
                if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
                if (board[ni][nj] == 2) air_cnt++;
            }
            if (air_cnt >= 2)
            {
                new_board[i][j] = 2;
                cnt++;
            }
        }
    }
    board = new_board;
    return cnt;
}

int solution(const int N, const int M, vector<vector<int>>& board)
{
    int depth = 0;
    while (true)
    {
        // board에 진짜 외곽(2)을 표기하기
        vector<vector<bool>> visited(N, vector<bool>(M, false));
        visited[0][0] = true; board[0][0] = 2;
        dfs(N, M, 0, 0, board, visited);

        // board에서 외곽과 마주하는 cheese를 삭제하기
        if (remove_cheese(N, M, board) == 0)
            break;
        depth++;
    }
    return depth;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<vector<int>> board(N, vector<int>(M));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> board[i][j];

    cout << solution(N, M, board);

    return 0;
}