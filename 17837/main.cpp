#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 현재 높이를 구할 수 있어야 함.
// 순서대로 실행시킬 수 있어야 함.
// 쌓여있으면 한 번에 이동시킬 수 있어야 함.
// change direction이 가능해야 함.
// 뒤집기가 가능해야 함.

vector<vector<int>> d = { {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

int change_direction(const int direction) {
    if (direction < 2) {
        return (direction == 0) ? 1 : 0;
    } else {
        return (direction == 2) ? 3 : 2;
    }
}

bool is_finish(const vector<vector<vector<int>>>& horse_in_board) {
    for (int i = 0; i < horse_in_board.size(); ++i) {
        for (int j = 0; j < horse_in_board[i].size(); ++j) {
            if (horse_in_board[i][j].size() > 3) return true;
        }
    }
    return false;
}

void move(const int horse_no, vector<vector<int>>& horses, const vector<vector<int>>& board, vector<vector<vector<int>>>& horse_in_board) {
    const unsigned long N = board.size();

    int ny = horses[horse_no][0] + d[horses[horse_no][2]][0];
    int nx = horses[horse_no][1] + d[horses[horse_no][2]][1];

    bool is_changed = false;

    // 벽인 경우
    if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
        horses[horse_no][2] = change_direction(horses[horse_no][2]);
        is_changed = true;

        ny = horses[horse_no][0] + d[horses[horse_no][2]][0];
        nx = horses[horse_no][1] + d[horses[horse_no][2]][1];
    }
    // 방향을 바꾸자마자 바로 또 벽일 가능성은 없음.
    // 파란색인 경우
    if (board[ny][nx] == 2) {
        if (is_changed) return;
        horses[horse_no][2] = change_direction(horses[horse_no][2]);

        ny = horses[horse_no][0] + d[horses[horse_no][2]][0];
        nx = horses[horse_no][1] + d[horses[horse_no][2]][1];

        if (ny < 0 || ny >= N || nx < 0 || nx >= N) return;
        if (board[ny][nx] == 2) return;
    }
    vector<int> full_stack = horse_in_board[horses[horse_no][0]][horses[horse_no][1]];
    vector<int> my_stack;
    const vector<int>::iterator it = find(full_stack.begin(), full_stack.end(), horse_no);
    my_stack.assign(it, full_stack.end());
    horse_in_board[horses[horse_no][0]][horses[horse_no][1]].assign(full_stack.begin(), it);

    if (board[ny][nx] == 1) {
        reverse(my_stack.begin(), my_stack.end());
    }
    horse_in_board[ny][nx].insert(horse_in_board[ny][nx].end(), my_stack.begin(), my_stack.end());
    for (int i = 0; i < my_stack.size(); ++i) {
        horses[my_stack[i]][0] = ny;
        horses[my_stack[i]][1] = nx;
    }
}

int solution(const int N, const int K, const vector<vector<int>>& board, vector<vector<int>>& horses) {
    vector<vector<vector<int>>> horse_in_board(N, vector<vector<int>>(N));
    for (int i = 0; i < horses.size(); ++i) {
        horse_in_board[horses[i][0]][horses[i][1]].push_back(i);
    }

    if (is_finish(horse_in_board)) return 0;

    int turn = 1;
    while (turn <= 1000) {
        for (int i = 0; i < K; ++i) {
            move(i, horses, board, horse_in_board);
            if (is_finish(horse_in_board)) return turn;
        }
        turn++;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }
    vector<vector<int>> horses(K, vector<int>(3));
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> horses[i][j];
            horses[i][j]--;
        }
    }

    cout << solution(N, K, board, horses);

    return 0;
}