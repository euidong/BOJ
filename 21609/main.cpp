#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> ds = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void search_group(const int y, const int x, vector<vector<int>>& block_group, const vector<vector<int>>& board, vector<vector<bool>>& visited) {
    const int N = board.size();

    for (int i = 0; i < 4; ++i) {
        const int ny = y + ds[i][0], nx = x + ds[i][1];
        if (ny > -1 && ny < N && nx > -1 && nx < N && !visited[ny][nx]) {
            if (board[ny][nx] == block_group[0][2] || board[ny][nx] == 0) {
                visited[ny][nx] = true;
                block_group.push_back({ny, nx, board[ny][nx]});
                search_group(ny, nx, block_group, board, visited);
            }
        }
    }
}

vector<vector<vector<int>>> get_block_groups(const int N, const vector<vector<int>>& board) {
    vector<vector<bool>> visited(N, vector<bool>(N, false));

    vector<vector<vector<int>>> block_groups;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (!visited[i][j] && board[i][j] > 0) {
                visited[i][j] = true;
                vector<vector<int>> block_group = {{ i, j, board[i][j]}};
                search_group(i, j, block_group, board, visited);
                if (block_group.size() > 1) block_groups.push_back(block_group);
                // 무지개 블락은 visited 초기화 필요함.
                for (int b_id = 0; b_id < block_group.size(); ++b_id) {
                    if(block_group[b_id][2] == 0) {
                        visited[block_group[b_id][0]][block_group[b_id][1]] = false;
                    }
                }
            }
        }
    }

    return block_groups;
}

void apply_gravity(const int N, vector<vector<int>>& board) {
    // head가 무슨 블락인지 확인
    // - 검은 블락인 경우, head += 1; end = head;
    // - 빈 경우, [end, head-1] block 모두 이동 / head += 1; end += 1;
    // - 그 외의 경우, head 한 칸 이동 / head += 1;
    for (int col = 0; col < N; ++col) {
        int head = 0, end = 0;
        for (; head < N; ++head) {
            if (board[head][col] == -1) {end = head + 1;}
            else if (board[head][col] == -2) {
                for (int i = head-1; i >= end; i--) {
                    board[i+1][col] = board[i][col];
                    board[i][col] = -2;
                }
                end++;
            }
        }
    }
}

void rotate_board_ccw(const int N, vector<vector<int>>& board) {
    vector<vector<int>> r_board(N, vector<int>(N));

    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            r_board[i][j] = board[j][N-1-i];
        }
    }

    board = r_board;
}

int solution(const int N, vector<vector<int>>& board) {
    int score = 0;

    while(true) {
        // block groups 구하기
        const vector<vector<vector<int>>> block_groups = get_block_groups(N, board);

        // block group가 없으면 종료
        if (block_groups.empty()) break;

        // 가장 큰 블록 그룹 찾기
        vector<int> candidates;
        int biggest_group_size = 1;
        for (int i = 0; i < block_groups.size(); ++i) {
            const int group_size = block_groups[i].size();
            if (biggest_group_size < group_size) {
                biggest_group_size = group_size;
                candidates = { i };
            } else if (biggest_group_size == group_size) {
                candidates.push_back(i);
            }
        }
        int biggest_group_id = candidates[0];
        if (candidates.size() > 1) {
            // 무지개 갯수가 많은 거 고르기
            int max_rainbow_cnt = 0;
            vector<int> new_candidates;
            for (int i = 0; i < candidates.size(); ++i) {
                const vector<vector<int>> block_group = block_groups[candidates[i]];
                int rainbow_cnt = 0;
                for (int j = 0; j < block_group.size(); ++j) {
                    if (block_group[j][2] == 0) rainbow_cnt++;
                }
                if (max_rainbow_cnt < rainbow_cnt) {
                    max_rainbow_cnt = rainbow_cnt;
                    new_candidates = { candidates[i] };
                } else if (max_rainbow_cnt == rainbow_cnt) {
                    new_candidates.push_back(candidates[i]);
                }
            }
            candidates = new_candidates;
            if (candidates.size() == 1) {
                biggest_group_id = candidates[0];
            } else {
                // 행, 열이 더 큰 거 고르기
                int max_row = -1, max_col = -1;
                for (int i = 0; i < candidates.size(); ++i) {
                    const vector<int> base = block_groups[candidates[i]][0];
                    const int y = base[0], x = base[1];
                    if (max_row < y) {
                        max_row = y; max_col = x;
                        biggest_group_id = candidates[i];
                    } else if (max_row == y && max_col < x) {
                        max_col = x;
                        biggest_group_id = candidates[i];
                    }
                }
            }
        }

        // 해당 블록 삭제
        for (int i = 0; i < block_groups[biggest_group_id].size(); ++i) {
            const vector<int> block = block_groups[biggest_group_id][i];
            board[block[0]][block[1]] = -2; // 빈칸은 -2
        }

        // 점수 추가
        score += biggest_group_size * biggest_group_size;

        // 중력 적용
        apply_gravity(N, board);

        // board 반시계 방향으로 90도 회전
        rotate_board_ccw(N, board);

        // 중력 적용
        apply_gravity(N, board);
    }
    return score;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> board[i][j];
    cout << solution(N, board);

    return 0;
}