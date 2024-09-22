#include <iostream>
#include <vector>

using namespace std;

long long init_tree(vector<long long>& seg_tree, const vector<long long>& nums, const int search_start, const int search_end, const int tree_idx) {
    if (search_start == search_end)
        return seg_tree[tree_idx] = nums[search_start];
    const int mid = (search_start + search_end) / 2;
    return seg_tree[tree_idx] = init_tree(seg_tree, nums, search_start, mid, tree_idx * 2) + init_tree(seg_tree, nums, mid + 1, search_end, tree_idx * 2 + 1);
}

long long get_sum(vector<long long>& seg_tree, const int search_start, const int search_end, const int range_start, const int range_end, const int tree_idx) {
    if (range_start > search_end) return 0;
    if (range_end < search_start) return 0;
    if (range_start <= search_start && range_end >= search_end) {
        return seg_tree[tree_idx];
    }
    const int mid = (search_start + search_end) / 2;
    return get_sum(seg_tree, search_start, mid, range_start, range_end, tree_idx*2) + \
        get_sum(seg_tree, mid+1, search_end, range_start, range_end, tree_idx*2 + 1);
}

void update(vector<long long>& seg_tree, const int search_start, const int search_end, const int tree_idx, const int target_idx, const long long diff) {
    if (search_start > target_idx) return;
    if (search_end < target_idx) return;
    seg_tree[tree_idx] += diff;
    if (search_start == search_end) return;
    const int mid = (search_start + search_end) / 2;
    if (mid >= target_idx)
        update(seg_tree, search_start, mid, tree_idx * 2, target_idx, diff);
    else
        update(seg_tree, mid+1, search_end, tree_idx * 2 + 1, target_idx, diff);
}

long long update_v2(vector<long long>& seg_tree, const int search_start, const int search_end, const int tree_idx, const int target_idx, const long long value) {
    if (search_start > target_idx) return 0;
    if (search_end < target_idx) return 0;
    if (search_start == search_end)
    {
        if (search_start == target_idx)
        {
            const long long origin = seg_tree[tree_idx];
            seg_tree[tree_idx] = value;
            return value - origin;
        }
        return 0;
    }

    const int mid = (search_start + search_end) / 2;
    if (mid >= target_idx)
    {
        const long long diff = update_v2(seg_tree, search_start, mid, tree_idx * 2, target_idx, value);
        seg_tree[tree_idx] += diff;
        return diff;
    }
    const long long diff = update_v2(seg_tree, mid+1, search_end, tree_idx * 2 + 1, target_idx, value);
    seg_tree[tree_idx] += diff;
    return diff;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K; cin >> N >> M >> K;
    vector<long long> nums(N); for (long long i = 0; i < N; ++i) cin >> nums[i];
    vector<long long> seg_tree(4*N);
    init_tree(seg_tree, nums, 0, N-1, 1);

    int a, b;
    long long c;
    for (long long i = 0; i < M+K; ++i) {
        cin >> a >> b >> c;
        if (a == 1) {
            const long long origin = get_sum(seg_tree, 0, N-1, b-1, b-1, 1);
            update(seg_tree, 0, N-1, 1, b-1, c - origin);
            // update_v2(seg_tree, 0, N-1, 1, b-1, c);
        } else {
            cout << get_sum(seg_tree, 0, N-1, b-1, c-1, 1) << '\n';
        }
    }

    return 0;
}