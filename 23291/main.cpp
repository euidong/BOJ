#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotate_matrix(const int N, const int M, vector<vector<int>>& matrix) {
    vector<vector<int>> r_matrix(M, vector<int>(N, 0));

    for (int m = 0; m < M; ++m)
    {
        for (int n = 0; n < N; ++n)
        {
            r_matrix[m][n] = matrix[N-1-n][m];
        }
    }
    matrix = r_matrix;
}

vector<vector<int>> directions = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

void adjust_matrix(const int N, const int M, vector<vector<int>>& matrix)
{
    vector<vector<int>> adjusted_matrix(matrix.begin(), matrix.end());

    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < M; ++x)
        {
            if (matrix[y][x] == -1) continue;
            for (int d = 0; d < 4; ++d)
            {
                const int ny = y + directions[d][0], nx = x + directions[d][1];
                if (ny > -1 && ny < N && nx > -1 && nx < M && matrix[ny][nx] != -1)
                {
                    if (matrix[ny][nx] >= matrix[y][x]) continue;
                    const int delta = (matrix[y][x] - matrix[ny][nx]) / 5;
                    if (delta > 0)
                    {
                        adjusted_matrix[y][x] -= delta;
                        adjusted_matrix[ny][nx] += delta;
                    }
                }
            }
        }
    }
    matrix = adjusted_matrix;
}

vector<int> flatten_matrix(const int N, const int M, const vector<vector<int>>& matrix)
{
    vector<int> fish_tank;
    for (int col = 0; col < M; ++col)
    {
        for (int row = N-1; row > -1; --row)
        {
            if (matrix[row][col] != -1)
                fish_tank.push_back(matrix[row][col]);
        }
    }
    return fish_tank;
}

int solution(const int N, const int K, vector<int>& fish_tank) {
    int organize_cnt = 0;

    // 종료 여부 판단하기
    while (K < *max_element(fish_tank.begin(), fish_tank.end()) - *min_element(fish_tank.begin(), fish_tank.end())) {
        // 가장 물고기가 적은 어항들에 물고기 한 마리씩 넣기
        vector<int> min_fish_tank_ids;
        int min_fish_num = 10001 * N;

        for (int f_id = 0; f_id < N; ++f_id)
        {
            if (min_fish_num > fish_tank[f_id])
            {
                min_fish_num = fish_tank[f_id];
                min_fish_tank_ids = {f_id};
            } else if (min_fish_num == fish_tank[f_id])
            {
                min_fish_tank_ids.push_back(f_id);
            }
        }
        for (const auto & f_id : min_fish_tank_ids)
            fish_tank[f_id]++;

        // [1 단계 정리하기]
        vector<vector<int>> matrix = {{ fish_tank[0] } };
        fish_tank.erase(fish_tank.begin());
        int n = 1, m = 1;
        // 종료 여부 판단하기
        while(n <= fish_tank.size())
        {
            // 회전시키기
            rotate_matrix(n, m, matrix);
            // fish tank의 요소 통합시키기
            matrix.push_back(vector<int>(fish_tank.begin(), fish_tank.begin() + n));

            // fish tank에서 통합된 내용 제거
            fish_tank.erase(fish_tank.begin(), fish_tank.begin() + n);

            n = matrix.size(); m = matrix[0].size();
        }

        vector<vector<int>> square(n, vector<int>(m + fish_tank.size(), -1));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) square[i][j] = matrix[i][j];
        for (int i = 0; i < fish_tank.size(); ++i) square[n-1][m+i] = fish_tank[i];

        // 조정하기
        adjust_matrix(square.size(), square[0].size(), square);

        // 일자로 피기
        fish_tank = flatten_matrix(square.size(), square[0].size(), square);

        // 2 단계 정리하기
        matrix = vector<vector<int>>(1, fish_tank);


        for (int i = 1; i <= 2; ++i)
        {
            n = i, m = fish_tank.size() / (2 * i);
            vector<vector<int>> left, right;
            for (int j = 0; j < n; ++j)
            {
                left.push_back(vector<int>(matrix[j].begin(), matrix[j].begin() + m));
                right.push_back(vector<int>(matrix[j].begin() + m, matrix[j].end()));
            }
            rotate_matrix(n, m, left); rotate_matrix(m, n, left);
            matrix = vector<vector<int>>();
            for (const auto & l : left) matrix.push_back(l);
            for (const auto & r : right) matrix.push_back(r);
        }

        adjust_matrix(matrix.size(), matrix[0].size(), matrix);

        fish_tank = flatten_matrix(matrix.size(), matrix[0].size(), matrix);

        organize_cnt++;
    }

    return organize_cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, K; cin >> N >> K;
    vector<int> fish_tank(N);
    for (int n = 0; n < N; ++n) cin >> fish_tank[n];

    cout << solution(N, K, fish_tank);

    return 0;
}