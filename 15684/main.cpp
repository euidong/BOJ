#include <iostream>
#include <vector>

using namespace std;

bool check_success(const int N, const int H, const vector<vector<vector<int>>>& graph) {
    const vector<int> dns = {-1, 1};
    for (int start_n = 0; start_n < N; start_n++) {
        int n = start_n;
        for (int h = 0; h < H; h++) {
            for (int i = 0; i < dns.size(); ++i) {
                const int nn = n + dns[i];
                if (-1 < nn && nn < N && graph[h][nn][n]) {
                    n = nn;
                    break;
                }
            }
        }
        if (n != start_n) return false;
    }
    return true;
}

int dfs(const int N, const int H, vector<vector<vector<int>>>& graph, const int depth, const int h_start, const int n_start) {
    if (check_success(N, H, graph)) return depth;
    if (depth == 3) return -1;
    int min_value = 4;
    for (int h = h_start; h < H; ++h) {
        for (int n = (h == h_start ? n_start : 0); n < N - 1; ++n) {
            const int l_n = n - 1;
            const int r_n = n + 1;
            const int rr_n = n + 2;
            if (l_n > -1 && graph[h][l_n][n] == 1) continue;
            if (graph[h][n][r_n] == 1) continue;
            if (rr_n < N && graph[h][r_n][rr_n] == 1) continue;

            graph[h][n][r_n] = 1;
            graph[h][r_n][n] = 1;
            const int next_n = n < N - 1 ? n + 1: 0;
            const int next_h = n < N - 1 ? h : h + 1;
            const int value = dfs(N, H, graph, depth + 1, next_h, next_n);
            if (value != -1 && value < min_value) {
                min_value = value;
            }
            graph[h][n][r_n] = 0;
            graph[h][r_n][n] = 0;

        }
    }
    if (min_value != 4) return min_value;
    return -1;
}


int solution(const int N, const int H, vector<vector<vector<int>>>& graph) {
    return dfs(N, H, graph, 0, 0, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, H;
    cin >> N >> M >> H;

    vector<vector<vector<int>>> graph(H, vector<vector<int>>(N, vector<int>(N, 0)));

    for (int i = 0; i < M; ++i) {
        int h, n;
        cin >> h >> n;
        graph[h-1][n-1][n] = 1;
        graph[h-1][n][n-1] = 1;
    }

    cout << solution(N, H, graph);

    return 0;
}