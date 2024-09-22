#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int DIST_LIMIT = 101;

void dfs_group(const int N, const int cur, const int group_id, const vector<vector<bool>>& adj, vector<int>& group_ids)
{
    for (int i = 0; i < N; ++i)
    {
        if (adj[cur][i] && group_ids[i] == -1)
        {
            group_ids[i] = group_id;
            dfs_group(N, i, group_id, adj, group_ids);
        }
    }
}

vector<vector<int>> make_groups(const int N, const vector<vector<bool>>& adj)
{
    vector<int> group_ids(N, -1);

    int group_id = 0;
    for (int i = 0; i < N; ++i)
    {
        if (group_ids[i] == -1)
        {
            group_ids[i] = group_id;
            dfs_group(N, i, group_id, adj, group_ids);
            group_id++;
        }
    }

    vector<vector<int>> groups(group_id);
    for (int i = 0; i < N; ++i)
        groups[group_ids[i]].push_back(i);

    return groups;
}

int elect_delegate(const vector<vector<bool>>& adj, const vector<int> group)
{
    vector<vector<int>> dists(group.size(), vector<int>(group.size(), DIST_LIMIT));

    for (int i = 0; i < group.size(); ++i)
    {
        for (int j = 0; j < group.size(); ++j)
        {
            if (i == j) dists[i][j] = 0;
            if (adj[group[i]][group[j]]) dists[i][j] = 1;
        }
    }

    for (int k = 0; k < group.size(); ++k)
    {
        for (int i = 0; i < group.size(); ++i)
        {
            for (int j = 0; j < group.size(); ++j)
            {
                if (dists[i][j] > dists[i][k] + dists[k][j])
                    dists[i][j] = dists[i][k] + dists[k][j];
            }
        }
    }

    int min_idx = -1, min_v = DIST_LIMIT;
    for (int i = 0; i < group.size(); ++i)
    {
        const int max_dist = *max_element(dists[i].begin(), dists[i].end());
        if (min_v > max_dist)
        {
            min_v = max_dist;
            min_idx = i;
        }
    }
    return group[min_idx];
}


vector<int> solution(const int N, const vector<vector<bool>>& adj)
{
    vector<int> answer;

    // 1. dfs로 그룹을 찾는다.
    vector<vector<int>> groups = make_groups(N, adj);
    // 2. group에서 중간 점 찾기 (floyd warshall 이후 거리의 최댓값의 최솟값 찾기)
    for (const auto & group : groups)
    {
        const int delegate = elect_delegate(adj, group);
        answer.push_back(delegate + 1);
    }
    sort(answer.begin(), answer.end());
    answer.insert(answer.begin(), groups.size());

    return answer;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M; cin >> N >> M;

    vector<vector<bool>> adj(N, vector<bool>(N, false));
    for (int i = 0; i < M; ++i)
    {
        int a, b; cin >> a >> b;
        adj[a-1][b-1] = adj[b-1][a-1] = true;
    }

    const vector<int> answer = solution(N, adj);

    for (const int num : answer) cout << num << '\n';
    return 0;
}