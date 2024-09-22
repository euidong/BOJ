#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool dfs(const vector<vector<bool>>& adj, vector<bool>& visited, const int cur, const int dst) {
    for (int next = 0; next < adj[cur].size(); ++next) {
        if (!adj[cur][next]) continue;
        if (visited[next]) continue;
        visited[next] = true;
        if (next == dst) return true;
        if (dfs(adj, visited, next, dst)) return true;
    }
    return false;
}

string solution(const int n, const vector<int>& start, const vector<vector<int>>& stores, const vector<int>& end) {
    vector<vector<bool>> adj(n+2, vector<bool>(n+2, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            const int dist = abs(stores[i][0] - stores[j][0]) + abs(stores[i][1] - stores[j][1]);
            if (dist <= 1000) adj[i][j] = adj[j][i] = true;
        }
        const int dist_start = abs(stores[i][0] - start[0]) + abs(stores[i][1] - start[1]);
        if (dist_start <= 1000) adj[n][i] = adj[i][n] = true;
        const int dist_end = abs(stores[i][0] - end[0]) + abs(stores[i][1] - end[1]);
        if (dist_end <= 1000) adj[n+1][i] = adj[i][n+1] = true;
    }
    adj[n][n] = adj[n+1][n+1] = true;
    adj[n][n+1] = (1000 >= abs(start[0] - end[0]) + abs(start[1] - end[1]));
    vector<bool> visited(n+2, false);
    visited[n] = true;
    if (dfs(adj, visited, n, n+1)) return "happy";
    else return "sad";
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int n; cin >> n;
        vector<int> start(2); cin >> start[0] >> start[1];
        vector<vector<int>> stores(n, vector<int>(2));
        for (int i = 0; i < n; ++i) cin >> stores[i][0] >> stores[i][1];
        vector<int> end(2); cin >> end[0] >> end[1];

        cout << solution(n, start, stores, end) << '\n';
    }
    return 0;
}