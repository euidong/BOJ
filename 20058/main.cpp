#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void rotate_matrix(vector<vector<int>>& board) {
    const int size = board.size();
    vector<vector<int>> r_board(board.begin(), board.end());
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            r_board[i][j] = board[size-1 - j][i];
        }
    }
    board = r_board;
}

vector<vector<vector<int>>> separate_board(const int N, const int L, const vector<vector<int>>& board) {
    const int board_size = pow(2, N);
    const int piece_size = pow(2, L);
    const int line_num = board_size / piece_size;
    const int piece_num = pow(line_num, 2);

    vector<vector<vector<int>>> pieces(piece_num, vector<vector<int>>(piece_size, vector<int>(piece_size)));

    for (int i = 0; i < piece_num; ++i) {
        const int start_y = (i / line_num) * piece_size;
        const int start_x = (i % line_num) * piece_size;
        for (int j = 0; j < piece_size; ++j) {
            pieces[i][j].assign(board[start_y+j].begin() + start_x, board[start_y+j].begin() + start_x + piece_size);
        }
    }
    return pieces;
}

void merge_pieces(vector<vector<int>>& board, const vector<vector<vector<int>>>& pieces) {
    const int line_num = sqrt(pieces.size());
    const int piece_size = pieces[0].size();
    for (int i = 0; i < line_num; ++i) {
        for (int j = 0; j < line_num; ++j) {
            const int piece_id = i * line_num + j;
            const int start_y = i * piece_size, start_x = j * piece_size;
            for (int n = 0; n < piece_size; ++n) {
                for (int m = 0; m < piece_size; ++m) {
                    board[start_y+n][start_x+m] = pieces[piece_id][n][m];
                }
            }
        }
    }
}

vector<vector<int>> ds = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs_for_melting(vector<vector<int>>& new_board, const vector<vector<int>>& board, vector<vector<bool>>& visited, const int y, const int x) {
    int near_count = 0;
    for (int i = 0; i < 4;++i) {
        const int ny = y + ds[i][0], nx = x + ds[i][1];
        if (ny > -1 && ny < board.size() && nx > -1 && nx < board.size() && board[ny][nx] > 0) {
            near_count++;
            if (!visited[ny][nx]) {
                visited[ny][nx] = true;
                dfs_for_melting(new_board, board, visited, ny, nx);
            }
        }
    }
    if (near_count < 3) new_board[y][x]--;
}

void dfs_all_for_melting(vector<vector<int>>& board) {
    vector<vector<int>> new_board(board.begin(), board.end());
    const int size = board.size();
    vector<vector<bool>> visited(size, vector<bool>(size, false));

    for (int i = 0; i < size; ++i) {
        for (int j =0; j < size; ++j) {
            if (board[i][j] > 0 && !visited[i][j]) {
                visited[i][j] = true;
                dfs_for_melting(new_board, board, visited, i, j);
            }
        }
    }
    board = new_board;
}

vector<int> dfs_for_counting(const vector<vector<int>>& board, vector<vector<bool>>& visited, const int y, const int x) {
    int ice_num = board[y][x];
    int piece_num = 1;
    for (int i = 0; i < 4;++i) {
        const int ny = y + ds[i][0], nx = x + ds[i][1];
        if (ny > -1 && ny < board.size() && nx > -1 && nx < board.size() && board[ny][nx] > 0 && !visited[ny][nx]) {
            visited[ny][nx] = true;
            const vector<int> result = dfs_for_counting(board, visited, ny, nx);
            ice_num += result[0];
            piece_num += result[1];
        }
    }
    return { ice_num, piece_num };
}

vector<int> dfs_all_for_counting(const vector<vector<int>>& board) {
    const int size = board.size();
    vector<vector<bool>> visited(size, vector<bool>(size, false));

    int tot_ice_num = 0, max_piece_size = 0;
    for (int i = 0; i < size; ++i) {
        for (int j =0; j < size; ++j) {
            if (board[i][j] > 0 && !visited[i][j]) {
                visited[i][j] = true;
                vector<int> result = dfs_for_counting(board, visited, i, j);
                tot_ice_num += result[0];
                max_piece_size = max(max_piece_size, result[1]);
            }
        }
    }

    return { tot_ice_num, max_piece_size };
}

vector<int> solution(const int N, const int Q, vector<vector<int>>& board, const vector<int>& Ls) {
    for (int i = 0; i < Q; ++i) {
        const int L = Ls[i];
        vector<vector<vector<int>>> pieces = separate_board(N, L, board);
        for (int j = 0 ; j < pieces.size(); ++j) {
            rotate_matrix(pieces[j]);
        }
        // 재조합
        merge_pieces(board, pieces);

        // 얼음깎기
        dfs_all_for_melting(board);
    }

    // 계산하기
    return dfs_all_for_counting(board);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, Q; cin >> N >> Q;
    const int size = pow(2, N);
    vector<vector<int>> board(size, vector<int>(size));
    for (int i = 0; i < size; ++i) for (int j = 0; j < size; j++) cin >> board[i][j];
    vector<int> Ls(Q);
    for (int i = 0; i < Q; ++i) cin >> Ls[i];

    const vector<int> answer = solution(N, Q, board, Ls);
    cout << answer[0] << '\n' << answer[1];

    return 0;
}