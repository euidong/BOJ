#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


const int MIN_LIMIT = -1;
const int MAX_LIMIT = 9 * 100000 + 1;
const int deltas[3] = {-1, 0, 1};

int prev_mins[3] = {MAX_LIMIT, MAX_LIMIT, MAX_LIMIT};
int prev_maxes[3] = {MIN_LIMIT, MIN_LIMIT, MIN_LIMIT};

short board[100000][3];

int min_dp(const int x, const int cur_v)
{
    int min_v = MAX_LIMIT;
    for (const int delta : deltas)
    {
        const int nx = delta + x;
        if (nx > -1 && nx < 3)
            min_v = min(min_v, cur_v + prev_mins[nx]);
    }

    return min_v;
}

int max_dp(const int x, const int cur_v)
{
    int max_v = MIN_LIMIT;
    for (const int delta : deltas)
    {
        const int nx = delta + x;
        if (nx > -1 && nx < 3)
            max_v = max(max_v, cur_v + prev_maxes[nx]);
    }
    return max_v;
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N; cin >> N;

    // vector<vector<short>>(N, vector<short>(3)); // N <= 100000, board <= 2bytes x 1000 x 100 x 3 = 600 kB
    for (int i = 0; i < N; ++i)
    {
        cin >> board[i][0] >> board[i][1] >> board[i][2];
    }


    for (int i = 0; i < 3; ++i)
        prev_maxes[i] = prev_mins[i] = board[0][i];


    for (int i = 1; i < N; ++i)
    {
        const int cur_maxes[3] = { max_dp(0, board[i][0]), max_dp(1, board[i][1]), max_dp(2, board[i][2])};
        const int cur_mins[3] = { min_dp(0, board[i][0]), min_dp(1, board[i][1]), min_dp(2, board[i][2])};

        for (int j = 0; j < 3; ++j)
        {
            prev_maxes[j] = cur_maxes[j];
            prev_mins[j] = cur_mins[j];
        }
    }

    int max_v = MIN_LIMIT, min_v = MAX_LIMIT;
    for (int i = 0; i < 3; ++i)
    {
        max_v = max(max_v, prev_maxes[i]);
        min_v = min(min_v, prev_mins[i]);
    }

    cout << max_v << ' ' << min_v;

    return 0;
}