#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_SIZE = 100001;
// 반복하는 중?
vector<int> solution(const int N, const int K)
{
    if (N == K) return {0, 1};
    // depth 마다 반복
    queue<vector<int>> q;
    q.push({N, 0});

    vector<vector<int>> visit_cnt(2, vector<int>(MAX_SIZE, 0)); visit_cnt[0][N] = 1;
    vector<bool> visited(MAX_SIZE, false); visited[N] = true;
    int cur_idx = 0, depth = 0;
    while (!q.empty())
    {
        const int cur_pos = q.front()[0], cur_depth = q.front()[1];
        q.pop();

        if (depth != cur_depth)
        {
            depth = cur_depth;
            cur_idx = (cur_idx + 1) % 2;
        }

        for (const auto operand : {-1, 1, cur_pos})
        {
            const int next_pos = cur_pos + operand;
            if (next_pos > -1 && next_pos < MAX_SIZE)
            {
                if (next_pos == K)
                {
                    int cnt = 0;
                    if (K-1 > -1) cnt += visit_cnt[cur_idx][K-1];
                    if (K+1 < MAX_SIZE) cnt += visit_cnt[cur_idx][K+1];
                    if (K % 2 == 0) cnt += visit_cnt[cur_idx][K/2];
                    return { cur_depth + 1, cnt };
                }
                if (!visited[next_pos])
                    q.push({next_pos, cur_depth + 1});
                visited[next_pos] = true;
                visit_cnt[(cur_idx+1)%2][next_pos] += visit_cnt[cur_idx][cur_pos];
            }
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N, K; cin >> N >> K;

    const vector<int> answer = solution(N, K);
    cout << answer[0] << '\n' << answer[1];
}