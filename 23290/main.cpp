#include <cmath>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> directions_for_fish = {
    {0, -1}, {-1, -1}, {-1, 0}, {-1, 1},
    {0, 1}, {1, 1}, {1, 0}, {1, -1}
};

vector<vector<int>> directions_for_shark = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}}; // 상좌하우

void move_fish(
    const vector<int>& fish, const vector<int>& shark, const vector<vector<int>>& smell_board,
    vector<vector<int>>& moved_fishes, vector<vector<vector<int>>>& fish_board) {

    const int y = fish[0], x = fish[1], d = fish[2];
    bool is_moved = false;

    for (int dd = 0; dd < 8; ++dd) {
        const int nd = d - dd >= 0 ? d - dd : 8 + d-dd;
        const int ny = y + directions_for_fish[nd][0];
        const int nx = x + directions_for_fish[nd][1];

        if (ny < 0 || ny >=4 || nx < 0 || nx >= 4) continue;
        if (shark[0] == ny && shark[1] == nx) continue;
        if (smell_board[ny][nx] > 0) continue;

        moved_fishes.push_back({ny, nx, nd });
        fish_board[ny][nx].push_back(moved_fishes.size() - 1);
        is_moved = true;
        break;
    }
    if (!is_moved) {
        moved_fishes.push_back({y, x, d});
        fish_board[y][x].push_back(moved_fishes.size() - 1);
    }
}

void move_shark(vector<int>& shark, vector<vector<int>>& moved_fishes, vector<vector<int>>& smell_board, vector<vector<vector<int>>>& fish_board) {
    vector<int> best = { -1, -1 }; // eat_cnt, dict_no

    queue<pair<vector<int>, vector<vector<vector<int>>>>> q;
    vector<int> shark_info = {shark[0], shark[1], 0, 0, 0};
    vector<vector<vector<int>>> copied_fish_board = fish_board;
    q.push(make_pair(shark_info, copied_fish_board));

    while (!q.empty()) {
        const auto cur = q.front();
        q.pop();

        const int y = cur.first[0], x = cur.first[1], move_cnt = cur.first[2], eat_cnt = cur.first[3], dict_no = cur.first[4];
        vector<vector<vector<int>>> cur_fish_board = cur.second;

        for (int d = 0; d < 4; ++d) {
            const int ny = y + directions_for_shark[d][0];
            const int nx = x + directions_for_shark[d][1];
            if (ny > -1 && ny < 4 && nx > -1 && nx < 4) {
                const int next_eat_cnt = eat_cnt + cur_fish_board[ny][nx].size();
                const int next_dict_no = dict_no + (d + 1) * pow(10, 2 - move_cnt);

                if (move_cnt == 2) {
                    if (best[0] < next_eat_cnt) {
                        best = { next_eat_cnt, next_dict_no };
                    } else if (best[0] == next_eat_cnt && best[1] > next_dict_no) {
                        best[1] = next_dict_no;
                    }
                    continue;
                }
                cur_fish_board[ny][nx] = vector<int>();
                vector<int> next_shark_info = { ny, nx, move_cnt + 1, next_eat_cnt, next_dict_no };
                q.push(make_pair(next_shark_info, cur_fish_board));
            }
        }
    }

    const string str_dict_no = to_string(best[1]);
    int y = shark[0], x = shark[1];
    for (const auto char_digit : str_dict_no) {
        const int digit = char_digit - '0';
        const int ny = y + directions_for_shark[digit - 1][0];
        const int nx = x + directions_for_shark[digit - 1][1];
        for (const auto fish_id : fish_board[ny][nx]) {
            const vector<int> fish = moved_fishes[fish_id];
            smell_board[fish[0]][fish[1]] = 3;
            moved_fishes[fish_id] = vector<int>();
        }
        fish_board[ny][nx] = vector<int>();
        y = ny, x = nx;
    }
    shark[0] = y; shark[1] = x;
    vector<vector<int>> new_fishes;
    for (const auto & fish : moved_fishes) {
        if (fish.empty()) continue;
        new_fishes.push_back(fish);
    }
    moved_fishes = new_fishes;
}

void reduce_smell(vector<vector<int>>& smell_board) {
    for (auto & row : smell_board) {
        for (auto & smell : row) {
            if (smell > 0) smell--;
        }
    }
}

int solution(const int M, const int S, vector<vector<int>>& fishes, vector<int>& shark) {
    vector<vector<int>> smell_board(4, vector<int>(4, 0));

    for (int s = 0; s < S; ++s) {
        // 물고기 이동 (격자범위, 상어, 냄새, 회전)
        vector<vector<vector<int>>> fish_board(4, vector<vector<int>>(4, vector<int>()));
        vector<vector<int>> moved_fishes;
        for (const auto & fish : fishes) {
            move_fish(fish, shark, smell_board, moved_fishes, fish_board);
        }

        // 상어 이동 (3칸 이동, 가장 많은 물고기가 있는 경로+사전순, 물고기 냄새 처리)
        move_shark(shark, moved_fishes, smell_board, fish_board);

        // 냄새 삭제
        reduce_smell(smell_board);

        // 물고기 복제
        fishes.insert(fishes.begin(), moved_fishes.begin(), moved_fishes.end());
    }

    return static_cast<int>(fishes.size());
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int M, S; cin >> M >> S;
    vector<vector<int>> fishes(M, vector<int>(3));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> fishes[i][j];
            fishes[i][j]--;
        }
    }
    vector<int> shark(2); cin >> shark[0] >> shark[1]; shark[0]--; shark[1]--;

    cout << solution(M, S, fishes, shark);
    return 0;
}