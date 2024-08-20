#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> direcs = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
const vector<vector<int>> left_spread_mask = {
    {0, 0, 2, 0, 0},
    {0, 10, 7, 1, 0},
    {5, -1, 0, 0, 0}, // alpha = -1로 마킹
    {0, 10, 7, 1, 0},
    {0, 0, 2, 0, 0}
};

vector<vector<int>> rotate_matrix(const vector<vector<int>>& matrix) {
    vector<vector<int>> r_matrix(matrix.begin(), matrix.end());

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            r_matrix[i][j] = matrix[j][matrix.size() - i - 1];
        }
    }

    return r_matrix;
}

void spread(vector<vector<int>>& board, const vector<vector<int>>& mask, const int y, const int x) {
    const int tot_sand = board[y][x];
    board[y][x] = 0;
    int remain_sand = tot_sand;
    vector<int> alpha_loc(2);
    for (int i = -2; i < 3; ++i) {
        for (int j = -2; j < 3; ++j) {
            if (mask[i+2][j+2] == -1) {
                alpha_loc = { y+i, x+j };
                continue;
            }
            const int moved_sand = tot_sand * mask[i+2][j+2] / 100;
            remain_sand -= moved_sand;
            board[y+i][x+j] += moved_sand;
        }
    }
    board[alpha_loc[0]][alpha_loc[1]] += remain_sand;
}

int solution(const int N, const vector<vector<int>>& board) {
    vector<vector<vector<int>>> spread_masks(4);

    spread_masks[0] = left_spread_mask;
    for (int i = 0; i < 3; ++i) {
        spread_masks[i+1] = rotate_matrix(spread_masks[i]);
    }
    int tot_sand = 0;
    vector<vector<int>> pad_board(N + 4, vector<int>(N + 4, 0));
    for (int i = 2; i < N + 2; ++i) {
        for (int j = 2; j < N + 2; ++j) {
            pad_board[i][j] = board[i-2][j-2];
            tot_sand += board[i-2][j-2];
        }
    }

    vector<int> wind(2, N / 2 + 2);
    int delta = 0; // 이동 거리
    int direc_id = -1; // 방향

    while (wind[0] != 2 || wind[1] != 2) {
        direc_id = (direc_id + 1) % 4;
        if (direc_id % 2 == 0) delta += 1; // 왼쪽 또는 오른쪽으로 이동할 때마다 1씩 증가
        if (wind[0] == 2) delta -= 1;
        const vector<vector<int>> cur_mask = spread_masks[direc_id];
        // delta만큼 이동하기
        for (int i = 0; i < delta; ++i) {
            const int ny = wind[0] + direcs[direc_id][0], nx = wind[1] + direcs[direc_id][1];
            spread(pad_board, cur_mask, ny, nx);
            wind[0] = ny; wind[1] = nx;
        }
    }

    int inside_sand = 0;
    for (int i = 2; i < N + 2; ++i) {
        for (int j = 2; j < N + 2; ++j) {
            inside_sand += pad_board[i][j];
        }
    }
    return tot_sand - inside_sand;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N; cin >> N;

    vector<vector<int>> board(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> board[i][j];

    cout << solution(N, board);
    return 0;
}