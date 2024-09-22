#include <iostream>
#include <vector>

using namespace std;

const int IMP_NUM = 1000000000 + 1;

vector<int> make_seg_tree(const vector<int>& A) {
    int K = 1; while(K < A.size()) K <<= 1;
    vector<int> seg_tree(K<<1, IMP_NUM);
    for (int i = 0; i < A.size(); ++i)
        seg_tree[i+K] = A[i];
    for (int i = K-1; i > 0; --i)
        seg_tree[i] = min(seg_tree[i<<1], seg_tree[i<<1|1]);
    return seg_tree;
}

int get_min_with_seg_tree(const vector<int>& seg_tree, const int range_start, const int range_end) {
    int left = range_start + (seg_tree.size() >> 1);
    int right = range_end + (seg_tree.size() >> 1);

    int min_v = IMP_NUM;
    while(left <= right)
    {
        if (left & 1)
        {
            min_v = min(min_v, seg_tree[left]);
            left+=1;
        }
        if (~right & 1)
        {
            min_v = min(min_v, seg_tree[right]);
            right-=1;
        }
        left >>= 1;
        right >>= 1;
    }
    return min_v;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int N, L; cin >> N >> L;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // O(NlogN)
    const vector<int> seg_tree = make_seg_tree(A);
    for (int i = 0; i < N; ++i) {
        cout << get_min_with_seg_tree(seg_tree, max(0, i-L+1), i) << ' ';
    }

    return 0;
}