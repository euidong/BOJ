#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, bool> is_exist;

void dfs(const int M, const int cur_m, const string& sequence, const vector<int>& nums)
{
    if (cur_m == M)
    {
        if(is_exist.find(sequence) == is_exist.end())
        {
            is_exist[sequence] = true;
            const string result(sequence.begin(), sequence.end() - 1);
            cout << result << '\n';
        }
        return;
    };
    for (int n = 0; n < nums.size(); ++n)
    {
        string next_sequence = sequence + to_string(nums[n]) + ' ';
        vector<int> next_nums(nums.begin(), nums.begin() + n);
        next_nums.insert(next_nums.end(), nums.begin() + n + 1, nums.end());
        dfs(M, cur_m + 1, next_sequence, next_nums);

    }
}

void solution(const int N, const int M, vector<int>& nums)
{
    sort(nums.begin(), nums.end());

    const string sequence = "";
    dfs(M, 0, sequence, nums);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> nums(N); for (int i = 0; i < N; ++i) cin >> nums[i];

    solution(N, M, nums);
    return 0;
}