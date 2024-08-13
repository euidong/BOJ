#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solve(const int N, const vector<vector<int>>& population) {
    int answer = N * N * 100;
    for (int x = 0; x < N - 1; ++x) {
        for (int y = 0; y < N - 1; ++y) {
            for (int d1 = 1; d1 <= y; ++d1) {
                for (int d2 = 1; d2 < N - y; ++d2) {
                    if (d1 + d2 + x >= N) continue;
                    vector<int> head(5, 0);
                    for (int i = 0; i < N; ++i) {
                        for (int j = 0; j < N; ++j) {
                            const int p = population[i][j];
                            if (i <= x) {
                                if (i == x && j == y) head[4] += p; // 5
                                else if (j <= y) head[0] += p; // 1
                                else head[1] += p; // 2
                            }
                            else if (i < x + d1 && j < y - (i - x)) head[0] += p;
                            else if (i <= x + d2 && j > y + (i - x)) head[1] += p;
                            else if (i >= x + d1 + d2) {
                                if (i == x + d1 + d2 && j == y - d1 + d2) head[4] += p;
                                else if (j < y - d1 + d2) head[2] += p;
                                else head[3] += p;
                            }
                            else if (i >= x + d1 && j < (y - d1) + (i - x - d1)) head[2] += p;
                            else if (i > x + d2 && j > (y + d2) - (i - x - d2)) head[3] += p;
                            else head[4] += p;
                        }
                    }
                    int candi = *max_element(head.begin(), head.end()) - *min_element(head.begin(), head.end());
                    answer = answer > candi ? candi: answer;
                }
            }
        }
    }
    return answer;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<vector<int> > population(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> population[i][j];
        }
    }

    cout << solve(N, population);

    return 0;
}