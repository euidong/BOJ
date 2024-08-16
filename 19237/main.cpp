#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> delta = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int solution(const int N, const int M, const int k, vector<vector<int>>& sharks, vector<vector<vector<int>>>& board, const vector<vector<vector<int>>>& priorities) {
    // 냄새가 있는 것과 없는 것을 구분하기 위함.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j].push_back(-1); // board[i][j][2] - 냄새를 뿌린 상어의 id
            board[i][j].push_back(-1); // board[i][j][3] - 남은 냄새 지속 시간
        }
    }

    for (int turn = 1; turn < 1001; ++turn) {
        // 냄새 뿌리고
        for (int i = 0; i < M; ++i) {
            if (sharks[i].empty()) continue;
            board[sharks[i][0]][sharks[i][1]][2] = i+1;
            board[sharks[i][0]][sharks[i][1]][3] = k;
        }

        //  이동 및 쫓아내고
        for (int i = M-1; i > -1; --i) { // 더 작은 id를 가진 상어만 살아남기 때문
            if (sharks[i].empty()) continue;
            const int y = sharks[i][0], x = sharks[i][1];
            const int direc = board[y][x][1];
            vector<int> second_best;
            for (int j = 0; j < 4; ++j) {
                const int n_direc = priorities[i][direc][j];
                const int ny = y + delta[n_direc][0];
                const int nx = x + delta[n_direc][1];
                if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue; // 범위 밖인 경우
                else if (board[ny][nx][2] == -1) { // 아무 냄새도 없는 경우
                    sharks[i][0] = ny; sharks[i][1] = nx;
                    board[y][x][0] = 0; board[y][x][1] = 0;
                    if (board[ny][nx][0] != 0 && board[ny][nx][0] > i+1) {
                        sharks[board[ny][nx][0]-1] = vector<int>();
                    }
                    board[ny][nx][0] = i+1; board[ny][nx][1] = n_direc;
                    second_best = vector<int>();
                    break;
                }
                else if (board[ny][nx][2] == i+1 && second_best.empty()) {
                    second_best = { ny, nx, i+1, n_direc };
                } // 내 냄새가 있는 경우
            }
            if (!second_best.empty()) {
                sharks[i][0] = second_best[0]; sharks[i][1] = second_best[1];
                board[y][x][0] = 0; board[y][x][1] = 0;
                board[second_best[0]][second_best[1]][0] = second_best[2]; board[second_best[0]][second_best[1]][1] = second_best[3];
            }
        }

        //  종료 여부 판단하고
        bool is_finished = true;
        for (int i = 1; i < sharks.size(); ++i) {
            if (!sharks[i].empty()) is_finished = false;
        }
        if (is_finished) return turn;

        //  냄새 지속시간 줄이고
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j][2] != -1) {
                    board[i][j][3] -= 1;
                    if (board[i][j][3] == 0) {
                        board[i][j][2] = -1;
                        board[i][j][3] = -1;
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, k;
    cin >> N >> M >> k;

    vector<vector<vector<int>>> board(N, vector<vector<int>>(N, vector<int>(2, 0)));
    vector<vector<int>> sharks(M);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j][0];
            if (board[i][j][0] != 0) {
                sharks[board[i][j][0] - 1] = {i, j};
            }
        }
    }
    for (int i = 0; i < M; ++i) {
        cin >> board[sharks[i][0]][sharks[i][1]][1];
        board[sharks[i][0]][sharks[i][1]][1]--;
    }

    vector<vector<vector<int>>> priorities(M, vector<vector<int>>(4, vector<int>(4)));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int l = 0; l < 4; ++l) {
                cin >> priorities[i][j][l];
                priorities[i][j][l]--;
            }
        }
    }

    cout << solution(N, M, k, sharks, board, priorities);
}