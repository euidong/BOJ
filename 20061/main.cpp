#include <iostream>
#include <vector>

using namespace std;

void delete_row(vector<vector<int>>& board, const int row_no) {
    for (int i = row_no; i > 0; --i) {
        board[i] = board[i-1];
    }
    board[0] = vector<int>(4, -1);
}

int drop(vector<vector<vector<int>>>& boards, const int cmd_no, const vector<int>& cmd) {
    int score = 0;

    vector<vector<int>> blocks(2);
    // block을 각 보드에 위치시킨다.
    if (cmd[0] == 1) {
        blocks[0] = {1, cmd[2], 1, cmd[2]};
        blocks[1] = {1, cmd[1], 1, cmd[1]};
    } else if (cmd[0] == 2) {
        blocks[0] = {1, cmd[2], 1, cmd[2] + 1};
        blocks[1] = {0, cmd[1], 1, cmd[1]};
    } else {
        blocks[0] = {0, cmd[2], 1, cmd[2]};
        blocks[1] = {1, cmd[1], 1, cmd[1] + 1};
    }
    for (int i = 0; i < 2; ++i) {
        // block 아래가 끝인지 아니면 뭐가 있는지 확인
        // - 끝이거나 뭐가 있으면 다음으로
        // - 아니면 아래로 한칸 내리기
        while (true) {
            vector<int> next;
            next.assign(blocks[i].begin(), blocks[i].end());
            for (int j = 0; j < next.size(); j += 2) {
                next[j] += 1;
            }

            if (next[0] < 8 && next[2] < 8 && boards[i][next[0]][next[1]] == -1 && boards[i][next[2]][next[3]] == -1) {
                blocks[i] = next;
            } else {
                break;
            }
        }
        boards[i][blocks[i][0]][blocks[i][1]] = cmd_no;
        boards[i][blocks[i][2]][blocks[i][3]] = cmd_no;

        // 행이나 열이 꽉 찼는지 확인
        // - 꽉 찬 게 있다.
        //   - 해당 부분 지우기
        //   - score 올리기
        //   - 위에 있던 블락 한칸씩 내리기
        // - 없다면, 넘어가기

        for (int j = 4; j < 8; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (boards[i][j][k] == -1) {
                    break;
                }
                if (k == 3) {
                    score++;
                    delete_row(boards[i], j);
                }
            }
        }

        // 옅은 부분(2~3 행 부분)에 블락이 있는 경우 그만큼 내리기
        for (int j = 2; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (boards[i][j][k] != -1) {
                    delete_row(boards[i], 7);
                    break;
                }
            }
        }
    }

    return score;
}


vector<int> solution(const int N, const vector<vector<int>>& cmds) {
    int score = 0;
    int remain_block = 0;

    // board[0] = green, board[1] = blue
    vector<vector<vector<int>>> boards(2, vector<vector<int>>(8, vector<int>(4, -1)));

    for (int i = 0; i < cmds.size(); ++i) {
        score += drop(boards, i, cmds[i]);
    }

    for (int k = 0; k < 2; ++k) {
        for (int i = 2; i < 8; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (boards[k][i][j] != -1) remain_block++;
            }
        }
    }

    return {score, remain_block};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;
    vector<vector<int>> cmds(N, vector<int>(3));
    for (int i = 0; i < N; ++i) {
        cin >> cmds[i][0] >> cmds[i][1] >> cmds[i][2];
    }
    const vector<int> answer = solution(N, cmds);
    cout << answer[0] << '\n' << answer[1];
    return 0;
}