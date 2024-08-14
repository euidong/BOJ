#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void rotate_by_id(const int id, vector<vector<int>>& board, const bool cw, int n) {
    vector<int> r_line;
    n %= board[id].size();
    if (cw == 0) {
        r_line.assign(board[id].end() - n, board[id].end());
        r_line.insert(r_line.end(), board[id].begin(), board[id].end() - n);
    } else {
        r_line.assign(board[id].begin(), board[id].begin() + n);
        r_line.insert(r_line.begin(), board[id].begin() + n, board[id].end());
    }
    board[id] = r_line;
}

void rotate(vector<vector<int>>& board, const vector<int>& cmd) {
    const int N = board.size();
    const int x = cmd[0];
    const int d = cmd[1];
    const int k = cmd[2];
    for (int i = x; i <= N; i += x) {
        rotate_by_id(i-1, board, d, k);
    }
}

vector<vector<int>> d = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

bool erase(const int N, const int M, vector<vector<int>>& board) {
    bool is_erased = false;
    vector<vector<int>> new_board(N, vector<int>(M));
    copy(board.begin(), board.end(), new_board.begin());
    queue<vector<int>> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    q.push({0, 0});
    visited[0][0] = true;
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            const int ny = cur[0] + d[i][0];
            int nx = cur[1] + d[i][1];
            if (nx == -1) nx = M-1;
            else if (nx == M) nx = 0;

            if (ny > -1 && ny < N) {
                if (board[ny][nx] != 0 && board[cur[0]][cur[1]] == board[ny][nx]) {
                    is_erased = true;
                    new_board[cur[0]][cur[1]] = 0;
                    new_board[ny][nx] = 0;
                }
                if (visited[ny][nx]) continue;
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
    board = new_board;
    return is_erased;
}

void normalize(const int N, const int M, vector<vector<int>>& board) {
    float avg = 0;
    int num = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] != 0) {
                num += 1;
                avg += board[i][j];
            }
        }
    }
    avg /= num;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (board[i][j] != 0) {
                if (board[i][j] < avg) board[i][j]++;
                else if (board[i][j] > avg) board[i][j]--;
            }
        }
    }
}

int solution(const int N, const int M, const int T, vector<vector<int>>& board, const vector<vector<int>>& cmds) {
    for (int i = 0; i < T; ++i) {
        rotate(board, cmds[i]);
        if (erase(N, M, board)) continue;
        normalize(N, M, board);
    }

    int answer = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            answer += board[i][j];
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, T;
    cin >> N >> M >> T;

    vector<vector<int>> board(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> board[i][j];
        }
    }

    vector<vector<int>> cmds(T, vector<int>(3));
    for (int i = 0; i < T; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> cmds[i][j];
        }
    }
    cout << solution(N, M, T, board, cmds);


    return 0;
}