#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> directions_for_dice = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void roll_dice(const int direction, vector<int>& dice) {
    vector<int> new_dice(3);
    if (direction == 0) {
        new_dice[0] = 7 - dice[1];
        new_dice[1] = dice[0];
        new_dice[2] = dice[2];
    } else if (direction == 1) {
        new_dice[0] = 7 - dice[2];
        new_dice[1] = dice[1];
        new_dice[2] = dice[0];
    } else if (direction == 2) {
        new_dice[0] = dice[1];
        new_dice[1] = 7 - dice[0];
        new_dice[2] = dice[2];
    } else {
        new_dice[0] = dice[2];
        new_dice[1] = dice[1];
        new_dice[2] = 7 - dice[0];
    }
    dice = new_dice;
}

int bottom_value(const vector<int>& dice) { return 7 - dice[0]; }

vector<vector<int>> same_score_travel_with_dfs(const int N, const int M, const vector<vector<int>>& board, vector<vector<bool>>& visited, const int score, const int y, const int x) {
    vector<vector<int>> acc;
    for (const auto & direction : directions_for_dice) {
        const int ny = y + direction[0], nx = x + direction[1];
        if (ny > -1 && ny < N && nx > -1 && nx < M && !visited[ny][nx] && board[ny][nx] == score) {
            visited[ny][nx] = true;
            acc.push_back({ ny, nx });
            vector<vector<int>> next = same_score_travel_with_dfs(N, M, board, visited, score, ny, nx);
            acc.insert(acc.end(), next.begin(), next.end());
        }
    }
    return acc;
}

vector<vector<int>> generate_score_board(const int N, const int M, const vector<vector<int>>& board) {
    vector<vector<int>> score_board(N, vector<int>(M, 0));

    vector<vector<bool>> visited(N, vector<bool>(M, false));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!visited[i][j]) {
                visited[i][j] = true;
                vector<vector<int>> path = same_score_travel_with_dfs(N, M, board, visited, board[i][j], i, j);
                path.push_back({i,j});
                for (const auto & point : path) {
                    score_board[point[0]][point[1]] = path.size() * board[i][j];
                }
            }
        }
    }

    return score_board;
}

int solution(const int N, const int M, const int K, const vector<vector<int>>& board) {
    int score = 0;

    const vector<vector<int>> score_board = generate_score_board(N, M, board);

    vector<int> dice = { 1, 3, 5 }; // 위, 오른, 앞, 아래, 뒷, 왼
    int direction = 0;

    int dice_y = 0, dice_x = 0;

    for (int k = 0; k < K; ++k) {
        // 주사위 이동
        int ny = dice_y + directions_for_dice[direction][0];
        int nx = dice_x + directions_for_dice[direction][1];

        if (ny < 0 || ny >= N || nx < 0 || nx >= M) {
            direction = (direction + 2) % 4;
            ny = dice_y + directions_for_dice[direction][0];
            nx = dice_x + directions_for_dice[direction][1];
        }
        dice_y = ny, dice_x = nx;
        roll_dice(direction, dice);

        score += score_board[dice_y][dice_x];

        const int A = bottom_value(dice);
        const int B = board[dice_y][dice_x];

        if (A > B) direction = (direction + 1) % 4;
        else if (A < B) direction = direction > 0 ? direction - 1 : 3;
    }

    return score;
}

int main() {
    int N, M, K; cin >> N >> M >> K;
    vector<vector<int>> board(N, vector<int>(M));
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> board[i][j];

    cout << solution(N, M, K, board);
}