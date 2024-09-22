#include <iostream>
#include <vector>

using namespace std;

long long init_seg_tree(vector<long long>& seg_tree, const vector<int>& nums, const pair<int, int>& search_range, const int tree_idx)
{
    if (search_range.first > search_range.second) return 0;
    if (search_range.first == search_range.second) return seg_tree[tree_idx] = nums[search_range.first];

    const int mid = (search_range.first + search_range.second) / 2;
    return seg_tree[tree_idx] = \
        init_seg_tree(seg_tree, nums, make_pair(search_range.first, mid), tree_idx * 2) + \
        init_seg_tree(seg_tree, nums, make_pair(mid + 1, search_range.second), tree_idx * 2 + 1);
}

long long get_sum(const vector<long long>& seg_tree, const pair<int, int>& search_range, const pair<int,int>& sum_range, const int tree_idx)
{
    if (search_range.first > sum_range.second || search_range.second < sum_range.first) return 0;
    if (search_range.first >= sum_range.first && search_range.second <= sum_range.second) return seg_tree[tree_idx];
    const int mid = (search_range.first + search_range.second) / 2;
    return get_sum(seg_tree, make_pair(search_range.first, mid), sum_range, tree_idx * 2) + \
            get_sum(seg_tree, make_pair(mid+1, search_range.second), sum_range, tree_idx * 2 + 1);
}

long long update(vector<long long>& seg_tree, const pair<int ,int>& search_range, const int tree_idx, const int target_idx, const int value)
{
    if (search_range.first > target_idx || search_range.second < target_idx) return 0;
    if (search_range.first == search_range.second && search_range.first == target_idx)
    {
        const long long diff = seg_tree[tree_idx] - value;
        seg_tree[tree_idx] = value;
        return diff;
    }
    const int mid = (search_range.first + search_range.second) / 2;
    long long diff;
    if (target_idx <= mid) // left
        diff = update(seg_tree, make_pair(search_range.first, mid), tree_idx * 2, target_idx, value);
    else // right
        diff = update(seg_tree, make_pair(mid+1, search_range.second), tree_idx * 2 + 1, target_idx, value);
    seg_tree[tree_idx] -= diff;
    return diff;
}

vector<long long> solution(const int N, const int Q, const vector<int>& nums, const vector<vector<int>>& actions)
{
    vector<long long> seg_tree(4*N);
    init_seg_tree(seg_tree, nums, make_pair(0, N-1), 1);

    vector<long long> answer;
    for (const auto & action : actions)
    {
        answer.push_back(get_sum(seg_tree, make_pair(0, N-1), make_pair(action[0], action[1]), 1));
        update(seg_tree, make_pair(0, N-1), 1, action[2], action[3]);
    }
    return answer;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, Q; cin >> N >> Q;
    vector<int> nums(N); for (int i = 0; i < N; ++i) cin >> nums[i];
    vector<vector<int>> actions(Q, vector<int>(4));
    int x, y, a, b;
    for (int i = 0; i < Q; ++i)
    {
        cin >> x >> y >> a >> b;
        if (x < y)
            actions[i] = { x-1, y-1, a-1, b };
        else
            actions[i] = { y-1, x-1, a-1, b };
    }

    vector<long long> answer = solution(N, Q, nums, actions);
    for (int i = 0; i < answer.size(); ++i)
        cout << answer[i] << '\n';
    return 0;
}