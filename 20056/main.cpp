#include <iostream>
#include <vector>

using namespace std;


void combine_fireballs(const int N, vector<vector<int>>& fireballs) {
    // board에 현재 상태 적용
    vector<vector<vector<int>>> board(N, vector<vector<int>>(N,vector<int>()));
    for (int j = 0; j < fireballs.size(); ++j) {
        board[fireballs[j][0]][fireballs[j][1]].push_back(j);
    }
    vector<vector<int>> next_fireballs;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j].empty()) continue;
            if (board[i][j].size() == 1) {
                vector<int> fireball = fireballs[board[i][j][0]];
                next_fireballs.push_back(fireball);
                continue;
            }
            int tot_m = 0, tot_s = 0;
            const int tot_num = board[i][j].size();
            bool is_all_even = true;
            bool is_all_odd = true;
            for (int k = 0; k < board[i][j].size(); ++k) {
                vector<int> fireball = fireballs[board[i][j][k]];
                tot_m += fireball[2]; tot_s += fireball[3];
                if (fireball[4] % 2 == 0) is_all_odd = false;
                else is_all_even = false;
            }
            const int m = tot_m / 5, s = tot_s / tot_num;
            if (m > 0) {
                vector<int> ds;
                if (is_all_even || is_all_odd)
                    ds = {0, 2, 4, 6};
                else
                    ds = {1, 3, 5, 7};
                for (int k = 0; k < ds.size(); ++k) {
                    next_fireballs.push_back({i, j, m, s, ds[k]});
                }
            }
        }
    }
    fireballs = next_fireballs;
}


vector<vector<int>> delta = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

int solution(const int N, const int M, const int K, vector<vector<int>>& fireballs) {
    vector<vector<vector<int>>> board;

    for (int i = 0; i < K; ++i) {
        // fireball 이동 수행
        // - 밖으로 나가면 순환
        vector<vector<int>> next_fireballs;
        for (int j = 0; j < fireballs.size(); ++j) {
            const int direc = fireballs[j][4];
            int nr = fireballs[j][0] + delta[direc][0] * fireballs[j][3];
            int nc = fireballs[j][1] + delta[direc][1] * fireballs[j][3];
            if (nr < 0) {
                nr = N + (nr % N);
                if (nr == N) nr = 0;
            }
            else if (nr >= N) nr %= N;
            if (nc < 0) {
                nc = N + (nc % N);
                if (nc == N) nc =0;
            }
            else if (nc >= N) nc %= N;

            next_fireballs.push_back({ nr, nc, fireballs[j][2], fireballs[j][3], fireballs[j][4]});
        }
        fireballs = next_fireballs;

        // fireball 합치기 처리
        combine_fireballs(N, fireballs);
        // fireball 크기가 2보다 작으면 종료.
        if (fireballs.size() < 2) break;
    }
    // 질량합 구하기
    int tot_m = 0;
    for (int j = 0; j < fireballs.size(); ++j) {
        tot_m += fireballs[j][2];
    }
    return tot_m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int N, M, K;
    cin >> N >> M >> K;
    vector<vector<int>> fireballs(M);
    for (int i = 0; i < M; ++i) {
        int r, c, m, s, d;
        cin >> r >> c >> m >> s >> d;
        fireballs[i] = {r - 1, c - 1, m, s, d};
    }

    cout << solution(N, M, K, fireballs);
}