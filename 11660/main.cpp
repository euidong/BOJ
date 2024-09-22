#include <iostream>
#include <vector>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(N, -1));
    vector<vector<long long>> acc(N, vector<long long>(N, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
            acc[i][j] = board[i][j];
            if (i > 0)
                acc[i][j] += acc[i-1][j];
            if (j > 0)
                acc[i][j] += acc[i][j-1];
            if (i > 0 && j > 0)
                acc[i][j] -= acc[i-1][j-1];
        }
    }

    int x1, y1, x2, y2;
    for (int i = 0; i < M; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        long long sum = acc[x2-1][y2-1];
        if (x1 > 1)
            sum -= acc[x1-2][y2-1];
        if (y1 > 1)
            sum -= acc[x2-1][y1-2];
        if (x1 > 1 && y1 > 1)
            sum += acc[x1-2][y1-2];
        cout << sum << '\n';
    }

    return 0;
}