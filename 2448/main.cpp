#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;

    int k = 0;
    while (pow(2, k) * 3 != N) k++;

    // 이전 pattern 3개를 이어붙이기
    // 일단 공백을 구함.
    // k = 0, blank_{0} = 0
    // k = 1, blank_{1} = 3
    // k = 2, blank_{2} = 6
    // k = 3, blank_{3} = 12
    // blank_{k} = N / 2;

    // 세로_{n} = 세로_{n-1} x 2
    // 가로_{n} = 가로_{n-1} x 2 + 1

    vector<vector<char>> pattern = {
        {' ', ' ', '*', ' ', ' '},
        {' ', '*', ' ', '*', ' '},
        {'*', '*', '*', '*', '*'}
    };

    for (int i = 0; i < k; ++i)
    {
        int top_blank_size = pattern[0].size() / 2 + 1;
        vector<vector<char>> next_pattern(pattern.size() * 2, vector<char>(pattern[0].size() * 2 + 1, ' '));
        const vector<vector<int>> stt_points = {
            {0, top_blank_size},
            {(int)pattern.size(), 0},
            {(int)pattern.size(), (int)pattern[0].size() + 1}
        };
        for (const auto stt : stt_points)
        {
            for (int dx = 0; dx < pattern.size(); ++dx)
            {
                for (int dy = 0; dy < pattern[0].size(); ++dy)
                {
                    next_pattern[stt[0]+dx][stt[1]+dy] = pattern[dx][dy];
                }
            }
        }
        pattern = next_pattern;
    }

    for (int i = 0; i < pattern.size(); ++i)
    {
        for (int j = 0; j < pattern[i].size(); ++j)
        {
            cout << pattern[i][j];
        }
        cout << '\n';
    }

    return 0;
}