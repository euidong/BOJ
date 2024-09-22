#include <iostream>
#include <vector>

using namespace std;

const long long DIVIDER = 1000000007;

vector<long long> make_seg_tree(const vector<int>& nums) {
    int half = 1; while(half < nums.size()) half <<= 1;
    vector<long long> seg_tree(half<<1, 1);
    for (int i = 0; i < nums.size(); ++i)
        seg_tree[i+half] = nums[i];
    for (int i = half -1; i > 0; --i)
        seg_tree[i] = (seg_tree[i<<1] * seg_tree[i<<1|1]) % DIVIDER;
    return seg_tree;
}

void update_seg_tree(vector<long long>& seg_tree, const long long target_idx, const long long value) {
    int tree_idx = target_idx + (seg_tree.size()>>1);

    seg_tree[tree_idx] = value;
    tree_idx>>=1;
    while (tree_idx > 0)
    {
        seg_tree[tree_idx] = (seg_tree[tree_idx<<1] * seg_tree[tree_idx<<1|1]) % DIVIDER;
        tree_idx>>=1;
    }

}

long long calc_seg_tree(const vector<long long>& seg_tree, const long long range_start, const long long range_end) {
    int stt = range_start|(seg_tree.size()>>1);
    int end = range_end|(seg_tree.size()>>1);

    long long product = 1;
    while (stt <= end) {
        if (stt & 1) {
            product = (product * seg_tree[stt]) % DIVIDER;
            stt+=1;
        }
        if (~end & 1) {
            product = (product * seg_tree[end]) % DIVIDER;
            end -= 1;
        }
        stt >>= 1;
        end >>= 1;
    }
    return product;
}

int main() {
    int N, M, K; cin >> N >> M >> K;
    vector<int> nums(N); for (int i = 0; i < N; ++i) cin >> nums[i];
    vector<long long> seg_tree = make_seg_tree(nums);
    long long a, b, c;
    for (int i = 0; i < M+K; ++i) {
        cin >> a >> b >> c;
        if (a == 1)
            update_seg_tree(seg_tree, b-1, c);
        else if (a == 2)
            cout << calc_seg_tree(seg_tree, b-1, c-1) << '\n';
    }
    return 0;
}