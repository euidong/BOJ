#include <iostream>
#include <vector>
#include <map>

using namespace std;

int get_range_sum_v1(const vector<int>& nums, const int range_start, const int range_end)
{
    int range_sum = 0;

    for (int i = range_start; i <= range_end; ++i) {
        range_sum += nums[i];
    }

    return range_sum;
}


vector<vector<int>> get_every_range_sum_v2(const int N, const vector<int>& nums)
{
    vector<vector<int>> range_sums(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
        range_sums[i][i] = nums[i];
        for (int j = i+1; j < N; ++j) {
            range_sums[i][j] = range_sums[i][j-1] + nums[j];
        }
    }

    return range_sums;
}

int get_range_sum_v2(const vector<vector<int>>& range_sums, const int range_start, const int range_end)
{
    return range_sums[range_start][range_end];
}



int calc_range_sum_v3(vector<vector<int>>& range_sums, const vector<int>& nums, const int start, const int end)
{
    if (start > end) return 0;
    if (start == end) return range_sums[start][end] = nums[start];
    const int mid = (start + end) / 2;
    return range_sums[start][end] = calc_range_sum_v3(range_sums, nums, start, mid) + calc_range_sum_v3(range_sums, nums, mid+1, end);
}

vector<vector<int>> get_specific_range_sums_v3(const int N, const vector<int>& nums)
{
    vector<vector<int>> range_sums(N, vector<int>(N, 0));
    calc_range_sum_v3(range_sums, nums, 0, N-1);
    return range_sums;
}


int get_range_sum_v3(const vector<vector<int>>& range_sums, const int range_start, const int range_end)
{
    if (range_start > range_end) return 0;
    if (range_start == range_end) return range_sums[range_start][range_end];
    const int mid = (range_start + range_end) / 2;

    return get_range_sum_v3(range_sums, range_start, mid) + get_range_sum_v3(range_sums, mid + 1, range_end);
}


void update_v3(vector<vector<int>>& range_sums, const int search_start, const int search_end, const int target_idx, const int diff)
{
    if (target_idx < search_start || target_idx > search_end) return;
    range_sums[search_start][search_end] += diff;
    if (search_start == search_end) return;

    const int mid = (search_start + search_end) / 2;
    if (target_idx <= mid) update_v3(range_sums, search_start, mid, target_idx, diff);
    else update_v3(range_sums, mid+1, search_end, target_idx, diff);
}



int calc_range_sum_v4(map<pair<int, int>, int>& range_sums, const vector<int>& nums, const int start, const int end)
{
    if (start > end) return 0;
    if (start == end)
    {
        range_sums.insert({ make_pair(start, end), nums[start] });
        return nums[start];
    }
    const int mid = (start + end) / 2;
    int value = calc_range_sum_v4(range_sums, nums, start, mid) + calc_range_sum_v4(range_sums, nums, mid+1, end);
    range_sums.insert({ make_pair(start, end), value });
    return value;
}

map<pair<int, int>, int> get_specific_range_sums_v4(const int N, const vector<int>& nums)
{
    map<pair<int, int>, int> range_sums;

    calc_range_sum_v4(range_sums, nums, 0, N-1);
    return range_sums;
}


int get_range_sum_v4(const map<pair<int, int>, int>& range_sums, const int range_start, const int range_end)
{
    if (range_start > range_end) return 0;
    if (range_start == range_end)
        return range_sums.find(make_pair(range_start, range_end))->second;
    const int mid = (range_start + range_end) / 2;

    return get_range_sum_v4(range_sums, range_start, mid) + get_range_sum_v4(range_sums, mid + 1, range_end);
}


void update_v4(map<pair<int, int>, int>& range_sums, const int search_start, const int search_end, const int target_idx, const int diff)
{
    if (target_idx < search_start || target_idx > search_end) return;
    range_sums.find(make_pair(search_start, search_end))->second += diff;

    if (search_start == search_end) return;

    const int mid = (search_start + search_end) / 2;
    if (target_idx <= mid) update_v4(range_sums, search_start, mid, target_idx, diff);
    else update_v4(range_sums, mid+1, search_end, target_idx, diff);
}


int fill_seg_tree(vector<int>& seg_tree, const vector<int>& nums, const int range_start, const int range_end, const int tree_idx)
{
    if (range_start == range_end)
        return seg_tree[tree_idx] = nums[range_start];

    const int mid = (range_start + range_end) / 2;
    return seg_tree[tree_idx] = fill_seg_tree(seg_tree, nums, range_start, mid, tree_idx * 2) + \
            fill_seg_tree(seg_tree, nums, mid + 1, range_end, tree_idx * 2 + 1);
}

vector<int> make_seg_tree(const vector<int>& nums)
{
    int K = 1; while(K < nums.size()) K *= 2;
    K *= 2;
    vector<int> seg_tree(K);
    fill_seg_tree(seg_tree, nums, 0, nums.size()-1, 1);
    return seg_tree;
}

int get_range_sum_with_seg_tree(const vector<int>& seg_tree, const int range_start, const int range_end, const int search_start, const int search_end, const int tree_idx)
{
    if (range_start > search_end || range_end < search_start) return 0;
    if (range_start <= search_start && range_end >= search_end) return seg_tree[tree_idx];
    const int search_mid = (search_start + search_end) / 2;
    return get_range_sum_with_seg_tree(seg_tree, range_start, range_end, search_start, search_mid, tree_idx * 2) + \
            get_range_sum_with_seg_tree(seg_tree, range_start, range_end, search_mid+1, search_end, tree_idx * 2 + 1);
}

void update_seg_tree(vector<int>& seg_tree, const int target_idx, const int diff, const int search_start, const int search_end, const int tree_idx)
{
    if (search_start > target_idx || search_end < target_idx) return;
    seg_tree[tree_idx] += diff;
    if (search_start == search_end) return;
    const int search_mid = (search_start + search_end) / 2;
    if (search_mid >= target_idx)
        update_seg_tree(seg_tree, target_idx, diff, search_start, search_mid, tree_idx * 2);
    else
        update_seg_tree(seg_tree, target_idx, diff, search_mid + 1, search_end, tree_idx * 2 + 1);
}



vector<int> make_seg_tree_v2(const vector<int>& nums)
{
    int K = 1; while(K < nums.size()) K <<= 1;
    K <<= 1;
    vector<int> seg_tree(K);
    for (int i = 0 ; i < nums.size(); ++i)
        seg_tree[i+(K>>1)] = nums[i];
    for (int i = (K>>1)-1; i > 0; --i)
        seg_tree[i]=seg_tree[i<<1]+seg_tree[i<<1|1];
    return seg_tree;
}

int get_range_sum_with_seg_tree_v2(const vector<int>& seg_tree, const int range_start, const int range_end)
{
    int left = range_start + (seg_tree.size()>>1);
    int right = range_end + (seg_tree.size()>>1);

    int sum = 0;
    while (left <= right)
    {
        if (left & 1) // 홀짝 판별 (홀수면 true)
        {
            sum += seg_tree[left];
            left = (left+1)>>1;
        }
        else
        {
            left >>= 1;
        }
        if (right & 1)
        {
            right >>= 1;
        }
        else
        {
            sum += seg_tree[right];
            right = (right-1)>>1;
        }

    }
    return sum;
}

void update_seg_tree_v2(vector<int>& seg_tree, const int target_idx, const int diff)
{
    int tree_idx = target_idx + (seg_tree.size()>>1);

    while (tree_idx > 0)
    {
        seg_tree[tree_idx] += diff;
        tree_idx >>= 1;
    }
}

int main() {
    const vector<int> nums = {1, 6, 4, 3, 8, 2, 7, 5};
    const vector<vector<int>> searches = {{0, 4}, {3, 5}, {2, 3}, {1, 5}, {2, 4}, {1, 1}, {2, 2}, {3, 5}}; // searches size = K
    const vector<vector<int>> updates = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 6}, {6, 7}, {7, 8} };

    // O(logN)
    vector<int> seg_tree = make_seg_tree_v2(nums);

    // O(KlogN)
    for (int i = 0; i < searches.size(); ++i) {
        cout << get_range_sum_with_seg_tree_v2(seg_tree, searches[i][0], searches[i][1]) << '\n';
        update_seg_tree_v2(seg_tree, updates[i][0], updates[i][1]);
    }

    return 0;
}

// 22
// 13
// 7
// 28
// 22
// 8
// 7
// 28

// 22
// 13
// 7
// 23
// 15
// 6
// 4
// 13