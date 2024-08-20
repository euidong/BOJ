#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> ds = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int solution(const int N, const vector<vector<int>>& students) {
    vector<vector<int>> be_liked_list(N*N + 1, vector<int>());
    vector<vector<int>> like_list(N*N + 1, vector<int>());
    for (int s = 0; s < students.size(); ++s) {
        const int like = students[s][0];
        for (int bs = 1; bs < students[s].size(); ++bs) {
            const int be_liked = students[s][bs];
            be_liked_list[be_liked].push_back(like);
            like_list[like].push_back(be_liked);
        }
    }

    vector<vector<int>> board(N, vector<int>(N, -1));
    vector<vector<vector<int>>> prior_boards(N*N+1, vector<vector<int>>(N, vector<int>(N, 0)));

    vector<vector<int>> empty_board(N, vector<int>(N, 4));
    for (int i = 0; i < N;++i) {
        for (int j = 0; j < N; ++j) {
            if (i == 0 || i == N-1)
                empty_board[i][j]--;
            if (j == 0 || j == N-1)
                empty_board[i][j]--;
        }
    }


    for (int s = 0; s < students.size(); ++s) {
        const int like = students[s][0];
        vector<vector<int>> candidates;
        // 자신이 좋아하는 학생의 위치 검색
        vector<vector<int>> prior_board = prior_boards[like];
        int cur_max_prior = 1;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] != -1) continue;
                if (prior_board[i][j] > cur_max_prior) {
                    candidates = { {i, j} };
                    cur_max_prior = prior_board[i][j];
                } else if (prior_board[i][j] == cur_max_prior) {
                    candidates.push_back({i, j});
                }
            }
        }
        // 빈 칸 점수 부여
        if (candidates.empty()) {
            int cur_max_empty = 0;
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (board[i][j] != -1) continue;
                    if (empty_board[i][j] > cur_max_empty) {
                        candidates = {{i,j}};
                        cur_max_empty = empty_board[i][j];
                    } else if (empty_board[i][j] == cur_max_empty) {
                        candidates.push_back({i, j});
                    }
                }
            }
        } else if (candidates.size() > 1) {
            vector<vector<int>> new_candidates;
            int cur_max_empty = 0;
            for (int i = 0; i < candidates.size(); ++i) {
                const int y = candidates[i][0], x = candidates[i][1];
                if (board[y][x] != -1) continue;
                if (empty_board[y][x] > cur_max_empty) {
                    new_candidates = {{ y, x}};
                    cur_max_empty = empty_board[y][x];
                } else if (empty_board[y][x] == cur_max_empty) {
                    new_candidates.push_back({y, x});
                }
            }
            candidates = new_candidates;
        }
        // n, m 위치보기
        vector<int> winner = candidates[0];

        // 인근에 설정 부여
        board[winner[0]][winner[1]] = like;
        for (int i = 0; i < 4; ++i) {
            const int ny = winner[0] + ds[i][0], nx = winner[1] + ds[i][1];
            if (ny > -1 && ny < N && nx > -1 && nx < N) {
                empty_board[ny][nx]--;
                for (int j = 0; j < be_liked_list[like].size(); ++j) {
                    const int be_liked = be_liked_list[like][j];
                    prior_boards[be_liked][ny][nx] += 1;
                }
            }
        }
    }

    // 만족도 계산
    int result = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            const int me = board[i][j];
            const vector<int> likes = like_list[me];

            int satisfaction = 0;
            for (int k = 0; k < 4; ++k) {
                const int ni = i + ds[k][0], nj = j + ds[k][1];
                if (ni > -1 && ni < N && nj > -1 && nj < N) {
                    if (find(likes.begin(), likes.end(), board[ni][nj]) != likes.end())
                        satisfaction++;
                }
            }
            if (satisfaction > 0) {
                result += pow(10, satisfaction - 1);
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N; cin >> N;

    const int size = N * N;
    vector<vector<int>> students(size, vector<int>(5, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> students[i][j];
            students[i][j];
        }
    }

    cout << solution(N, students);
}