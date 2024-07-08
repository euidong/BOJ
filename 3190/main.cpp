#include <iostream>
#include <vector>

using namespace std;

// 우, 하, 좌, 상
vector<vector<int>> direction = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int turn(const int d, const char c) {
    if (c == 'D') {
        return (d + 1) % 4;
    } else {
        return (d + 3) % 4;
    }
}

int solution(const int N, const int K, vector<pair<int, int>> apples, vector<pair<int, char>> rotation_points) {
    vector<vector<int>> graph (N, vector<int>(N, 0));
    for (int i = 0; i < apples.size(); ++i) {
        graph[apples[i].first][apples[i].second] = 1;
    }
    graph[0][0] = 2;

    pair<int, int> head = make_pair(0, 0);
    vector<pair<int, int>> snake;
    snake.push_back(head);

    int d = 0;
    int time = 0;

    while (true) {
        time += 1;

        int nhy = head.first + direction[d][0];
        int nhx = head.second + direction[d][1];

        if (-1 < nhy && nhy < N && -1 < nhx && nhx < N) {
            if (graph[nhy][nhx] == 2) {
                break;
            }
            else if (graph[nhy][nhx] == 1) {
                head = make_pair(nhy, nhx);
                graph[nhy][nhx] = 2;
                snake.insert(snake.begin(), head);
            }
            else {
                head = make_pair(nhy, nhx);
                graph[nhy][nhx] = 2;
                snake.insert(snake.begin(), head);
                graph[(snake.end() - 1)->first][(snake.end() - 1)->second] = 0;
                snake.pop_back();
            }
            if (rotation_points.size() > 0 && rotation_points[0].first == time) {
                d = turn(d, rotation_points[0].second);
                rotation_points.erase(rotation_points.begin());
            }
        } else {
            break;
        }

    }

    return time;
}

int main() {
    int N, K, R;

    cin >> N >> K;

    int f,s;
    vector<pair<int, int>> apples;
    for (int i = 0; i < K; ++i) {
        cin >> f >> s;
        apples.push_back(make_pair(f-1, s-1));
    }
    cin >> R;
    int t;
    char c;
    vector<pair<int, char>> rotation_points;
    for (int i = 0; i < R; ++i) {
        cin >> t >> c;
        rotation_points.push_back(make_pair(t, c));
    }
    const int time = solution(N, K, apples, rotation_points);
    cout << time << '\n';
    return 0;
}
