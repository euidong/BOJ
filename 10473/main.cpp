#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const double MAX_SECONDS = 102 * 500 * 1.5L;

double dijkstra(const int n, const int start, const int end, const vector<vector<double>>& graph)
{
    priority_queue<pair<double, int>> pq;
    vector<double> seconds(n, MAX_SECONDS);
    seconds[start] = 0;

    for (int i = 0; i < n; ++i)
    {
        if (i == start) continue;
        if (graph[start][i] != -1)
        {
            seconds[i] = graph[start][i];
            pq.push(make_pair(-graph[start][i], i));
        }
    }

    while (!pq.empty())
    {
        const pair<double, int> cur = pq.top();
        pq.pop();
        const double cur_second = -cur.first;
        const int cur_loc = cur.second;

        if (seconds[cur_loc] < cur_second) continue;
        for (int next_loc = 0; next_loc < n; ++next_loc)
        {
            if (seconds[cur_loc] + graph[cur_loc][next_loc] < seconds[next_loc])
            {
                seconds[next_loc] = seconds[cur_loc] + graph[cur_loc][next_loc];
                pq.push(make_pair(-seconds[next_loc], next_loc));
            }
        }
    }

    return seconds[end];
}

double solution(const vector<double>& me, const vector<double>& goal, const int n, const vector<vector<double>>& canons)
{
    vector<vector<double>> graph(n+2, vector<double>(n+2, 0));

    for (int i = 0; i < canons.size(); ++i)
    {
        for (int j = i; j < canons.size(); ++j)
        {
            const double x_dist = canons[i][0] - canons[j][0];
            const double y_dist = canons[i][1] - canons[j][1];
            const double dist =  sqrt(x_dist * x_dist + y_dist * y_dist);
            graph[i][j] = graph[j][i] = dist / 5L;
            const double second_with_canon = 2L + abs(dist - 50L) / 5L;
            if (graph[i][j] > second_with_canon)
                graph[i][j] = graph[j][i] = second_with_canon;
        }
        const double me_canon_x_dist = canons[i][0] - me[0];
        const double me_canon_y_dist = canons[i][1] - me[1];
        const double me_canon_dist = sqrt(me_canon_x_dist * me_canon_x_dist+ me_canon_y_dist * me_canon_y_dist);
        graph[n][i] = graph[i][n] = me_canon_dist / 5L;

        if (graph[i][n] > 2L + abs(me_canon_dist - 50L) / 5L)
            graph[i][n] = 2L + abs(me_canon_dist - 50L) / 5L;

        const double goal_canon_x_dist = canons[i][0] - goal[0];
        const double goal_canon_y_dist = canons[i][1] - goal[1];
        const double goal_canon_dist = sqrt(goal_canon_x_dist * goal_canon_x_dist + goal_canon_y_dist * goal_canon_y_dist);
        graph[n+1][i] = graph[i][n+1] = goal_canon_dist / 5L;
        if (graph[i][n+1] > 2L + abs(goal_canon_dist - 50L) / 5L)
            graph[i][n+1] = 2L + abs(goal_canon_dist - 50L) / 5L;
    }

    const double me_goal_x_dist = goal[0] - me[0];
    const double me_goal_y_dist = goal[1] - me[1];
    graph[n][n+1] = graph[n+1][n] = sqrt(me_goal_x_dist * me_goal_x_dist + me_goal_y_dist * me_goal_y_dist) / 5L;

    return dijkstra(n+2, n, n+1, graph);
}

int main()
{
    vector<double> me(2); cin >> me[0] >> me[1];
    vector<double> goal(2); cin >> goal[0] >> goal[1];
    int n; cin >> n;
    vector<vector<double>> canons(n, vector<double>(2));
    for (int i = 0; i < n; ++i) cin >> canons[i][0] >> canons[i][1];

    cout.precision(8);
    cout << solution(me, goal, n, canons);

    return 0;
}