#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

vector<vector<int>> delta = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};

int solution(vector<vector<vector<int>>>& board) {
    vector<vector<int>> fishes(17); // fishes[0] = 상어

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            fishes[board[i][j][0]] = {i, j};
        }
    }

    int max_score = 0;

    // 상어를 0,0 에 두기
    int score = board[0][0][0];
    fishes[board[0][0][0]] = vector<int>();
    fishes[0] = {0, 0};
    board[0][0][0] = 0;

    queue<tuple<vector<vector<int>>, vector<vector<vector<int>>>, int>> q;
    q.push(make_tuple(fishes, board, score));

    while (!q.empty()) {
        const tuple<vector<vector<int>>, vector<vector<vector<int>>>, int> top = q.front();
        q.pop();

        fishes = get<0>(top);
        board = get<1>(top);
        score = get<2>(top);

        // 물고기 차례대로 이동시키기
        for (int i = 1; i < fishes.size(); ++i) {
            if (fishes[i].empty()) continue;
            for (int j = 0; j < 8; ++j) { // TODO: 8방향 모두 이동못하는 경우 이동은 안함. 그런데 방향은 어떻게 할지 안정해짐. 확인필요.
                const int x = fishes[i][0], y = fishes[i][1];
                const int direc = board[x][y][1];
                const int nx = x + delta[direc][0], ny = y + delta[direc][1];

                if (nx > -1 && nx < 4 && ny > -1 && ny < 4) {
                    // swap(board[nx][ny], board[x][y])
                    // - 비어있는 경우
                    if (board[nx][ny].empty()) {
                        board[nx][ny] = {board[x][y][0], board[x][y][1]};
                        board[x][y] = vector<int>();
                        fishes[board[nx][ny][0]] = { nx, ny };
                        break;
                    }
                    // - 상어가 없는 경우
                    else if (board[nx][ny][0] != 0) {
                        const vector<int> temp = {board[nx][ny][0], board[nx][ny][1]};
                        board[nx][ny] = {board[x][y][0], board[x][y][1]};
                        board[x][y] = temp;
                        fishes[board[nx][ny][0]] = { nx, ny };
                        fishes[board[x][y][0]] = { x, y };
                        break;
                    }
                }
                // 회전
                board[x][y][1] = (board[x][y][1] + 1) % 8;
            }

        }

        // 상어가 이동할 수 있는 경우의 수를 다루기
        // 상어를 이동시킨 이후 queue에 넣기
        // (점수 추가, 보드 변경)
        int x = fishes[0][0], y = fishes[0][1];

        for (int d = 1; d < 4; ++d) {
            const int direc = board[x][y][1];
            const int nx = x + d * delta[direc][0], ny = y + d * delta[direc][1];
            if (nx > -1 && nx < 4 && ny > -1 && ny < 4) {
                if (!board[nx][ny].empty()) {
                    vector<vector<int>> next_fishes;
                    next_fishes.assign(fishes.begin(), fishes.end());
                    vector<vector<vector<int>>> next_board;
                    next_board.assign(board.begin(), board.end());
                    const int next_score = score + board[nx][ny][0];

                    next_fishes[board[nx][ny][0]] = vector<int>();
                    next_board[nx][ny][0] = 0;
                    next_fishes[0] = {nx, ny};
                    next_board[x][y] = vector<int>();

                    q.push(make_tuple(next_fishes, next_board, next_score));
                }
            } else {
                break;
            }
        }

        // 이동할 수없다면 최댓값과 비교후 종료
        if (max_score < score) max_score = score;
    }

    return max_score;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<vector<vector<int>>> board(4, vector<vector<int>>(4, vector<int>(2)));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int a, b;
            cin >> a >> b;
            board[i][j][0] = a;
            board[i][j][1] = b - 1;
        }
    }

    cout << solution(board);

    return 0;
}