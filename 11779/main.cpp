#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int DIST_LIMIT = 1000 * 100000 + 1;

pair<int, vector<int>> solution(const int n, const int m, const vector<vector<int>> adj[], const int src, const int dst)
{
    vector<int> dists(n, DIST_LIMIT);
    dists[src] = 0;
    vector<int> parents(n, -1);
    priority_queue<vector<int>> pq;
    pq.push({0, src});

    while (!pq.empty())
    {
        const int cur_dist = pq.top()[0], cur_loc = pq.top()[1];
        pq.pop();

        if (cur_dist > dists[cur_loc]) continue;
        for (const auto & next : adj[cur_loc])
        {
            const int next_loc = next[0], next_dist = next[1];

            if (dists[next_loc] > dists[cur_loc] + next_dist)
            {
                dists[next_loc] = dists[cur_loc] + next_dist;
                parents[next_loc] = cur_loc;
                pq.push({dists[next_loc], next_loc});
            }
        }
    }

    vector<int> path;
    int loc = dst;
    while (parents[loc] != -1)
    {
        path.push_back(loc + 1);
        loc = parents[loc];
    }
    path.push_back(src + 1);
    reverse(path.begin(), path.end());

    return make_pair(dists[dst], path);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int n, m; cin >> n >> m;

    vector<vector<int>> adj[n];
    int a, b, c;
    for (int i = 0; i < m; ++i)
    {
        cin >> a >> b >> c;
        adj[a-1].push_back({b-1, c});
    }

    int src, dst; cin >> src >> dst;

    const pair<int, vector<int>> answer = solution(n, m, adj, src - 1, dst - 1);

    cout << answer.first << '\n'
         << answer.second.size() << '\n';
    for (const auto ans : answer.second)
        cout << ans << ' ';

    return 0;
}