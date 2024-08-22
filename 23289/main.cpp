#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const vector<vector<int>> directions_for_start_point_radiator = {{}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};
const vector<vector<vector<int>>> directions_for_spread_radiator_heat = {
    {},
    {{-1, 1}, {0, 1}, {1, 1}}, // 우
    {{-1, -1}, {0, -1}, {1, -1}}, // 좌
    {{-1, -1}, {-1, 0}, {-1, 1}}, // 위
    {{1, -1}, {1, 0}, {1, 1}} // 아래
};


const vector<vector<vector<vector<int>>>> blockings_for_spread_radiator_heat = {
    {},
    {{{0, 0, -1, 0},{-1, 0, -1, 1}}, {{0, 0, 0, 1}}, {{0, 0, 1, 0}, {1, 0, 1, 1}}}, // 우
    {{{0, 0, -1, 0}, {-1, 0, -1, -1}}, {{0, 0, 0, -1}}, {{0, 0, 1, 0}, {1, 0, 1, -1}}}, // 좌
    {{{0, 0, 0, -1}, {0, -1, -1, -1}}, {{0, 0, -1, 0}}, {{0, 0, 0, 1}, {0, 1, -1, 1}}}, // 위
    {{{0, 0, 0, -1}, {0, -1, 1, -1}}, {{0, 0, 1, 0}}, {{0, 0, 0, 1},{0, 1, 1, 1}}} // 아래
};


void operate_radiators(
    const int R, const int C,
    const vector<vector<int>>& radiators,
    const vector<vector<vector<vector<bool>>>>& graph,
    vector<vector<int>>& board) {
    for (const auto & radiator : radiators) {
        const int first_y = radiator[0] + directions_for_start_point_radiator[radiator[2]][0];
        const int first_x = radiator[1] + directions_for_start_point_radiator[radiator[2]][1];

        if (first_y < 0 || first_y >= R || first_x < 0 || first_x >= C) continue;
        if (!graph[radiator[0]][radiator[1]][first_y][first_x]) continue;

        board[first_y][first_x] += 5;
        queue<vector<int>> q;
        q.push({first_y, first_x, radiator[2], 4 });
        vector<vector<bool>> visited(R, vector<bool>(C, false));
        visited[first_y][first_x] = true;

        while (!q.empty()) {
            const vector<int> cur = q.front();
            const int y = cur[0], x = cur[1], d = cur[2], h = cur[3];
            q.pop();

            for (int i = 0; i < 3; ++i) {
                const int dy = directions_for_spread_radiator_heat[d][i][0];
                const int dx = directions_for_spread_radiator_heat[d][i][1];
                const int ny = y + dy, nx = x + dx;
                const vector<vector<int>> blockings = blockings_for_spread_radiator_heat[d][i];
                if (ny > -1 && ny < R && nx > -1 && nx < C && !visited[ny][nx]) {
                    bool is_blocked = false;
                    for (const vector<int> & blocking : blockings) {
                        const int y1 = y + blocking[0], x1 = x + blocking[1];
                        const int y2 = y + blocking[2], x2 = x + blocking[3];
                        if (!graph[y1][x1][y2][x2]) {
                            is_blocked = true;
                            break;
                        }
                    }
                    if (is_blocked) continue;
                    board[ny][nx] += h;
                    visited[ny][nx] = true;
                    if (h == 1) continue;
                    q.push({ ny, nx, d, h - 1});
                }
            }
        }

    }
}

const vector<vector<int>> directions_for_adjustment = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void adjust_temperature(
    const int R, const int C,
    const vector<vector<vector<vector<bool>>>>& graph,
    vector<vector<int>>& board) {

    vector<vector<int>> new_board(board.begin(), board.end());
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] < 4) continue;
            for (int d = 0; d < 4; ++d) {
                const int ni = i + directions_for_adjustment[d][0];
                const int nj = j + directions_for_adjustment[d][1];
                if (ni > -1 && ni < R && nj > -1 && nj < C && graph[i][j][ni][nj]) {
                    if (board[i][j] <= board[ni][nj]) continue;
                    const int amount = (board[i][j] - board[ni][nj]) / 4;
                    new_board[i][j] -= amount;
                    new_board[ni][nj] += amount;
                }
            }
        }
    }

    board = new_board;
}

void reduce_temperature(const int R, const int C, vector<vector<int>>& board) {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (i == 0 || i == R-1 || j == 0 || j == C-1) {
                if (board[i][j] > 0) board[i][j]--;
            }
        }
    }
}

bool check_finish(
    const int K,
    const vector<vector<int>>& board,
    const vector<vector<int>>& targets) {
    for (const auto & target : targets) {
        if (board[target[0]][target[1]] < K) return false;
    }
    return true;
}

int solution(
        const int R, const int C, const int K, const int W,
        vector<vector<int>>& board, const vector<vector<int>>& walls
    ) {
    int chocolate_cnt = 0;

    vector<vector<int>> radiators;
    vector<vector<int>> targets;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (board[i][j] == 5) targets.push_back({i, j});
            else if (board[i][j] > 0) radiators.push_back({i, j, board[i][j]});
            board[i][j] = 0;
        }
    }

    vector<vector<vector<vector<bool>>>> graph(
        R, vector<vector<vector<bool>>>(
            C, vector<vector<bool>>(
                R, vector<bool>(C, true)
            )
        )
    );
    const vector<vector<int>> t_filter = {{-1, 0}, {0, 1}};

    for (const auto & wall : walls) {
        const int y = wall[0] - 1, x = wall[1] - 1;
        const int ny = y + t_filter[wall[2]][0], nx = x + t_filter[wall[2]][1];

        if (ny > -1 && ny < R && nx > -1 && nx < C) {
            graph[y][x][ny][nx] = false;
            graph[ny][nx][y][x] = false;
        }
    }

    while (true) {
        operate_radiators(R, C, radiators, graph, board);
        adjust_temperature(R, C, graph, board);
        reduce_temperature(R, C, board);
        chocolate_cnt++;
        if (check_finish(K, board, targets)) break;
        if (chocolate_cnt == 101) break;
    }

    return chocolate_cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int R, C, K; cin >> R >> C >> K;
    vector<vector<int>> board(R, vector<int>(C));
    for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) cin >> board[i][j];
    int W; cin >> W;
    vector<vector<int>> walls(W, vector<int>(3));
    for (int i = 0; i < W; ++i) for (int j = 0; j < 3; ++j) cin >> walls[i][j];

    cout << solution(R, C, K, W, board, walls);
}
