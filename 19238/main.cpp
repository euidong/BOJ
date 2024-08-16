#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> delta = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

int bfs_for_customer(const int y, const int x, const int ty, const int tx, const vector<vector<int>>& board) {
    if (y == ty && x == tx) return 0;
    const int N = board.size();
    queue<vector<int>> q;
    q.push({y, x, 0});
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[y][x] = true;
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            const int ny = cur[0] + delta[i][0], nx = cur[1] + delta[i][1];
            if (ny > -1 && ny < N && nx > -1 && nx < N && board[ny][nx] != 1 && !visited[ny][nx]) {
                if (ny == ty && nx == tx) return cur[2] + 1;
                visited[ny][nx] = true;
                q.push({ny, nx, cur[2] + 1});
            }
        }
    }
    return -1;
}

vector<int> bfs_for_taxi(vector<int>& taxi, vector<vector<int>>& board) {
    const int N = board.size();
    if (board[taxi[0]][taxi[1]] < 0) {
        return {board[taxi[0]][taxi[1]], 0};
    }
    queue<vector<int>> q;
    q.push({taxi[0], taxi[1], 0});
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    visited[taxi[0]][taxi[1]] = true;

    bool is_finished = false;
    vector<int> min_customer;
    while(!q.empty()) {
        vector<int> cur = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            const int ny = cur[0] + delta[i][0], nx = cur[1] + delta[i][1];
            if (ny > -1 && ny < N && nx > -1 && nx < N && board[ny][nx] != 1 && !visited[ny][nx]) {
                visited[ny][nx] = true;
                if (board[ny][nx] < 0) {
                    is_finished = true;
                    if (min_customer.empty()) {
                        min_customer = { ny, nx, cur[2] + 1 };
                    } else if (cur[2] == min_customer[2]) {
                        break;
                    } else if ((ny < min_customer[0]) || (ny == min_customer[0] && nx < min_customer[1])) {
                        min_customer = { ny, nx, cur[2] + 1 };
                    }
                }
                if (!is_finished) {
                    q.push({ny, nx, cur[2] + 1});
                }
            }
        }
    }
    if (is_finished) {
        return { board[min_customer[0]][min_customer[1]], min_customer[2] };
    } else {
        return { -1, -1 };
    }
}

int solution(const int N, const int M, int oil, vector<int>& taxi, vector<vector<int>>& board, vector<vector<int>>& customer) {
    for (int i = 0; i < M; ++i) {
        board[customer[i][0]][customer[i][1]] = -(i+1);
    }

    for (int i = 0; i < M; ++i) {
        // taxi와 거리가 가장 짧은 customer 찾기
        // - 벽을 고려할 것
        const vector<int> result = bfs_for_taxi(taxi, board);
        const int min_customer = -result[0]-1;
        const int min_dist = result[1];
        if (min_dist == -1) return -1; // 길이없음.
        board[customer[min_customer][0]][customer[min_customer][1]] = 0;

        // oil과 거리 비교 (oil이 더 작으면 종료)
        if (oil < min_dist) {
            return -1;
        }
        oil -= min_dist;
        const int next_dist = bfs_for_customer(customer[min_customer][0], customer[min_customer][1], customer[min_customer][2], customer[min_customer][3], board);
        if (next_dist == -1) return -1;
        if (oil < next_dist) {
            return -1;
        }
        oil += next_dist;
        taxi[0] = customer[min_customer][2];
        taxi[1] = customer[min_customer][3];
    }

    return oil;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, oil;
    cin >> N >> M >> oil;

    vector<vector<int>> board = vector<vector<int>>(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }
    vector<int> taxi(2);
    cin >> taxi[0] >> taxi[1];
    taxi[0]--; taxi[1]--;
    vector<vector<int>> customer(M, vector<int>(4));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> customer[i][j];
            customer[i][j]--;
        }
    }

    cout << solution(N, M, oil, taxi, board, customer);

    return 0;
}