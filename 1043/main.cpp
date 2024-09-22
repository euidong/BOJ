#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int solution(const int N, const int M, vector<bool>& known, const vector<vector<int>>& parties)
{
    vector<vector<int>> party_list_by_guest(N);
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < parties[i].size(); ++j)
        {
            party_list_by_guest[parties[i][j]].push_back(i);
        }
    }

    vector<bool> visited(M, false);
    queue<int> q;
    for (int guest_id = 0; guest_id < N; ++guest_id)
    {
        if (known[guest_id])
        {
            for (const int party_id : party_list_by_guest[guest_id])
            {
                if (visited[party_id]) continue;
                q.push(party_id);
                visited[party_id];
            }
        }
    }

    while(!q.empty())
    {
        const int cur_party_id = q.front();
        q.pop();

        for (const auto & guest_id : parties[cur_party_id])
        {
            known[guest_id] = true;
            for (const auto party_id : party_list_by_guest[guest_id])
            {
                if (visited[party_id]) continue;
                visited[party_id] = true;
                q.push(party_id);
            }
        }
    }


    // 진실을 알고 있는 사람이 있는 파티를 무조건 먼저 가야함. 왜냐하면, 과장을 했다가 후에 진실이 밝혀지는 것은 원치 않기 때문임.
    // queue에 진실을 알고 있는 사람이 있는 party를 넣기
    // 해당 party에서 새롭게 이를 알게 된 사람들이 속한 party도 queue에 넣기
    // - 특정 사람이 속한 party를 알아두면 유용할 듯
    // - 특정 파티를 반

    // dfs로 구현 시 2^50 (과장한다 or 안한다)
    // 양쪽에서 bfs를 하는 경우 (2 x 2^25)^2 = (2 x 1024 x 1024 x 32)^2 = (2 x 33554432)^2 = (67108864)^2

    // user에 묶인 party 형식으로 묶기

    int answer = 0;
    for (const auto v: visited) if(!v) answer++;

    return answer;
}

int main()
{
    int N, M; cin >> N >> M;
    vector<bool> known(N, false);
    int K; cin >> K;
    int num;
    for (int i = 0; i < K; ++i)
    {
        cin >> num;
        known[num-1] = true;
    }
    vector<vector<int>> parties(M);
    for (int i = 0; i < M; ++i)
    {
        int L; cin >> L;
        parties[i] = vector<int>(L);
        for (int j = 0; j < L; ++j)
        {
            cin >> parties[i][j];
            parties[i][j]--;
        }

    }

    cout << solution(N, M, known, parties);

    return 0;
}