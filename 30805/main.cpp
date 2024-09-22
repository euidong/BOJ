#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool comp_subset(const vector<int>& a, const vector<int>& b)
{
    int idx = 0;
    while (idx < min(a.size(), b.size()) && a[idx] == b[idx]) idx++;
    if (idx == min(a.size(), b.size())) return a.size() < b.size();
    return a[idx] < b[idx];
}

// [start] BFS version -> exceed memory if don't use comparing.
vector<int> solution_v1(const int N, const vector<int>& A, const int M, const vector<int>& B)
{
    vector<int> last_subset;

    // subset들을 모두 구하기
    // 1. 완전탐색 : A의 subset을 찾고, 해당 여부 확인
    queue<pair<vector<int>,vector<int>>> q;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (A[i] == B[j])
            {
                vector<int> subset = {A[i]};
                if (comp_subset(last_subset, subset))
                {
                    last_subset = subset;
                    vector<int> next = {i+1, j+1};
                    q.push(make_pair(next, subset));
                }
            }
        }
    }


    while (!q.empty())
    {
        pair<vector<int>, vector<int>> cur = q.front();
        q.pop();
        const int cur_i = cur.first[0], cur_j = cur.first[1];

        for (int i = cur_i; i < N; ++i)
        {
            for (int j = cur_j; j < M; ++j)
            {
                if (A[i] == B[j])
                {
                    vector<int> subset = cur.second;
                    subset.push_back(A[i]);
                    if (comp_subset(last_subset, subset))
                    {
                        last_subset = subset;
                        vector<int> next = {i+1, j+1};
                        q.push(make_pair(next, subset));
                    }
                }
            }
        }
    }

    return last_subset;
}
// [end] BFS version

// [start] DFS version -> exceed time
vector<int> last_subset;
void dfs(const int N, const vector<int>& A, const int M, const vector<int>& B, const int cur_i, const int cur_j, vector<int>& subset)
{
    for (int i = cur_i; i < N; ++i)
    {
        for (int j = cur_j; j < M; ++j)
        {
            if (A[i] == B[j])
            {
                subset.push_back(A[i]);
                if (comp_subset(last_subset, subset))
                {
                    last_subset = subset;
                    dfs(N, A, M, B, i+1, j+1, subset);
                }
                subset.pop_back();
            }
        }
    }
}

vector<int> solution_v2(const int N, const vector<int>& A, const int M, const vector<int>& B)
{
    last_subset.clear();
    vector<int> subset;
    dfs(N, A, M, B, 0, 0, subset);
    return last_subset;
}
// [end] DFS version

vector<int> solution(const int N, const vector<int>& A, const int M, const vector<int>& B)
{
    return solution_v1(N, A, M, B);
}

int main()
{
    int N; cin >> N;
    vector<int> A(N); for (int i = 0; i < N; ++i) cin >> A[i];

    int M; cin >> M;
    vector<int> B(M); for (int i = 0; i < M; ++i) cin >> B[i];

    const vector<int> answer = solution(N, A, M, B);

    cout << answer.size() << '\n';
    for (const auto a : answer)
        cout << a << ' ';

    return 0;
}