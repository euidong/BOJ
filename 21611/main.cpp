#include <iostream>
#include <vector>

using namespace std;

const vector<vector<int>> directions_for_board = {{0, -1}, {1, 0}, {0, 1}, {-1, 0} };
const vector<vector<int>> directions_for_blizzard = { {}, {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

void blizzard(const int N, vector<vector<int>>& board, const vector<int>& ds) {
    int y = N / 2, x = N / 2;
    const int dy = directions_for_blizzard[ds[0]][0], dx = directions_for_blizzard[ds[0]][1];
    for (int i = 0; i < ds[1]; ++i) {
        y = y + dy; x = x + dx;
        board[y][x] = 0;
    }
}

void move_beads(const vector<int*>& board_line_form) {
    int empty_cnt = 0;
    for (int i = 1; i < board_line_form.size(); ++i) {

        // 0이 아닌 수가 나올 때까지 검사하기
        while (true) {
            if (i+empty_cnt >= board_line_form.size()) {
                for (int j = i; j < board_line_form.size(); ++j)
                    *board_line_form[j] = 0;
                return;
            }
            const int next_bead_num = *board_line_form[i+empty_cnt];
            if (next_bead_num != 0) break;
            empty_cnt++;
        }

        *board_line_form[i] = *board_line_form[i+empty_cnt];
    }
}

int explode_beads(const vector<int*>& board_line_form) {
    int score = 0;
    int series_val = -1;
    int series_cnt = 0;
    int end_point = board_line_form.size() - 1;
    for (int i = 1; i < board_line_form.size(); ++i) {
        const int bead_num = *board_line_form[i];
        if (bead_num == 0) {
            end_point = i;
            break;
        }
        if (series_val == bead_num) {
            series_cnt++;
        } else {
            if (series_cnt >= 4) {
                for (int j = 0; j < series_cnt; ++j) {
                    *board_line_form[i-j-1] = 0;
                }
                score += series_val * series_cnt;
            }
            series_val = bead_num;
            series_cnt = 1;
        }
    }
    if (series_cnt >= 4) {
        for (int j = 0; j < series_cnt; ++j) {
            *board_line_form[end_point-j] = 0;
        }
        score += series_val * series_cnt;
    }
    return score;
}

void break_group(const vector<int*>& board_line_form) {
    if(*board_line_form[1] == 0) return;
    int bead_val = *board_line_form[1];
    int bead_cnt = 1;
    vector<int> new_beads;
    for (int i = 2; i < board_line_form.size(); ++i) {
        const int cur_bead_val = *board_line_form[i];
        if (cur_bead_val == 0) break;
        if (cur_bead_val == bead_val) bead_cnt++;
        else {
            new_beads.push_back(bead_cnt);
            new_beads.push_back(bead_val);
            bead_val = cur_bead_val;
            bead_cnt = 1;
        }
    }
    if (bead_cnt > 0) {
        new_beads.push_back(bead_cnt);
        new_beads.push_back(bead_val);
    }
    for (int i = 1; i < board_line_form.size(); ++i) {
        if (i <= new_beads.size()) *board_line_form[i] = new_beads[i-1];
        else *board_line_form[i] = 0;
    }
}

int solution(const int N, const int M, vector<vector<int>>& board, const vector<vector<int>>& ds_list) {
    int score = 0;

    vector<int*> board_line_form;
    int y = N / 2, x = N / 2;
    int d = -1, s = 0;
    while (x > -1) {
        d = (d + 1) % 4;
        if (d % 2 == 0) s++;

        for (int rd = 0; rd < s; ++rd) {
            board_line_form.push_back(&board[y][x]);
            y = y + directions_for_board[d][0];
            x = x + directions_for_board[d][1];
        }
    }

    for (const auto& ds : ds_list) {
        // 마법 시전
        blizzard(N, board, ds);

        // 구슬 이동
        move_beads(board_line_form);

        while (true) {
            // 4이상 연속하는 구슬 탐색 및 폭발 (없으면 종료, 폭발 시 점수 추가 유의)
            const int cur_score = explode_beads(board_line_form);
            if (cur_score == 0) break;
            score += cur_score;

            // 구슬 이동
            move_beads(board_line_form);
        }
        // 그룹 깨기
        break_group(board_line_form);
    }

    return score;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) for(int j = 0; j < N; ++j) cin >> board[i][j];
    vector<vector<int>> ds_list(M, vector<int>(2));
    for (int i = 0; i < M; ++i) cin >> ds_list[i][0] >> ds_list[i][1];

    cout << solution(N, M, board, ds_list);

    return 0;
}