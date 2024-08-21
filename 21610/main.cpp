#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> directions_for_move = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}};
vector<vector<int>> directions_for_copy = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

void move_cloud(const int N, vector<int>& cloud, const vector<int>& ds) {
    const vector<int> direction = directions_for_move[ds[0] - 1];
    const int speed = ds[1] % N; // speed가 보드보다 큰 경우 제한하기

    // 고려할 점 : 경계를 넘어가는 경우
    for (int i = 0; i < 2; ++i) {
        cloud[i] = (cloud[i] + speed * direction[i]) % N;
        if (cloud[i] < 0) cloud[i] += N;
    }
}

void copy_water(const int N, vector<vector<int>>& A, const vector<int>& cloud) {
    const int y = cloud[0], x = cloud[1];
    for (const auto & direction : directions_for_copy) {
        const int ny = y + direction[0], nx = x + direction[1];
        if (ny > -1 && ny < N && nx > -1 && nx < N && A[ny][nx] > 0) {
            A[y][x]++;
        }
    }
}

int solution(const int N, const int M, vector<vector<int>>& A, const vector<vector<int>>& ds_list) {
    vector<vector<int>> clouds = {{N-2, 0}, {N-2, 1}, {N-1, 0}, {N-1, 1}};
    for (const auto & ds : ds_list) {
        // 구름 이동 (-> 순환 가능)
        for (auto & cloud : clouds) {
            move_cloud(N, cloud, ds);
        }

        // 양동이에 물 추가
        for (const auto & cloud : clouds) {
            A[cloud[0]][cloud[1]]++;
        }

        // 물추가 칸에서 물복사 수행 (대각선에 물이 있으면 그 수 만큼 물 증가, 대각선 확인 시 순환 x)
        for (const auto & cloud : clouds) {
            copy_water(N, A, cloud);
        }

        // 구름 생성 (기존 구름이 있던 칸인 경우 제외)
        vector<vector<bool>> cloud_map(N, vector<bool>(N, false));
        for (const auto & cloud : clouds) cloud_map[cloud[0]][cloud[1]] = true;
        vector<vector<int>> new_clouds;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (!cloud_map[i][j] && A[i][j] > 1) {
                    new_clouds.push_back({i,j});
                    A[i][j] -= 2;
                }
            }
        }
        clouds = new_clouds;
    }

    // 양동이의 물의 양 총합 구하기
    int tot = 0;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) tot += A[i][j];
    return tot;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];
    vector<vector<int>> ds_list(M, vector<int>(2));
    for (int i = 0; i < M; ++i) cin >> ds_list[i][0] >> ds_list[i][1];

    cout << solution(N, M, A, ds_list);
}