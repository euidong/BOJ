#include <iostream>
#include <vector>

using namespace std;

// 우, 하, 좌, 상
vector<vector<vector<int>>> direction = {
    {},
    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}},
    {{1, 0, 1, 0}, {0, 1, 0, 1}},
    {{1, 0, 0, 1}, {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}},
    {{1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 0}, {0, 1, 1, 1}},
    {{1, 1, 1, 1}}
};

// 우, 하, 좌, 상
vector<vector<int>> delta = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

vector<int> rotate_camera(const vector<int>& camera) {
    int direction_cnt = direction[camera[2]].size();
    vector<int> r_camera = {
        camera[0],
        camera[1],
        camera[2],
        (camera[3] + 1) % direction_cnt
    };
    return r_camera;
}

vector<vector<int>> mark_room(vector<vector<int>>& room, const vector<int>& camera) {
    int N = room.size();
    int M = room[0].size();

    vector<int> camera_direction = direction[camera[2]][camera[3]];
    vector<vector<int>> filled_pos;

    for (int i = 0; i < camera_direction.size(); ++i) {
        if (camera_direction[i] == 0) {
            continue;
        }
        int y = camera[0];
        int x = camera[1];
        while (true) {
            int ny = y + delta[i][0];
            int nx = x + delta[i][1];

            if (-1 < ny && ny < N && -1 < nx && nx < M) {
                y = ny;
                x = nx;
                // 빈칸 or 채워진 칸
                if (room[ny][nx] == 0) {
                    room[ny][nx] = 7;
                    filled_pos.push_back({ny, nx});
                }
                // 벽
                else if (room[ny][nx] == 6) {
                    break;
                }
                // 카메라 칸 or 이미 채워진 칸
                else {
                    continue;
                }
            }
            // 바깥
            else {
                break;
            }
        }
    }
    return filled_pos;
}


int dfs(vector<vector<int>>& room, const vector<vector<int>>& cameras, int camera_idx) {
    int N = room.size();
    int M = room[0].size();
    if (camera_idx == cameras.size()) {
        int empty = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                if (room[i][j] == 0) empty++;
            }
        }
        return empty;
    }
    vector<int> camera = cameras[camera_idx];
    int camera_type = camera[2];

    int min_value = N * M;
    for (int i = 0; i < direction[camera_type].size(); ++i) {
        vector<vector<int>> filled_area = mark_room(room, camera);
        int value = dfs(room, cameras, camera_idx + 1);
        if (value < min_value) {
            min_value = value;
        }
        for (int j = 0; j < filled_area.size(); ++j) {
            int y = filled_area[j][0];
            int x = filled_area[j][1];
            room[y][x] = 0;
        }
        camera = rotate_camera(camera);
    }
    return min_value;
}


int solution(int N, int M, vector<vector<int>> room) {
    vector<vector<int>> cameras;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (room[i][j] != 0 && room[i][j] != 6) {
                // y, x, camera type, direction
                cameras.push_back({i, j, room[i][j], 0});
            }
        }
    }

    return dfs(room, cameras, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    int N, M;
    cin >> N >> M;

    vector<vector<int>> room(N, vector<int>(M, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> room[i][j];
        }
    }

    cout << solution(N, M, room);

    return 0;
}