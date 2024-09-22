#include <iostream>
#include <vector>

using namespace std;

const int MIN_LIMIT = 0;
const int MAX_LIMIT = 1000000001;

vector<vector<int>> make_seg_trees(const vector<int>& nums) {
    int half = 1; while(half < nums.size()) half<<=1;

    vector<vector<int>> seg_trees = {vector<int>(half<<1, MAX_LIMIT), vector<int>(half<<1, MIN_LIMIT)};
    for (int i = 0; i < nums.size(); ++i) {
        seg_trees[0][i+half] = nums[i];
        seg_trees[1][i+half] = nums[i];
    }
    for (int i = half-1; i > 0; --i) {
        seg_trees[0][i] = min(seg_trees[0][i<<1], seg_trees[0][i<<1|1]);
        seg_trees[1][i] = max(seg_trees[1][i<<1], seg_trees[1][i<<1|1]);
    }
    return seg_trees;
}

vector<int> get_range_min_and_max(const vector<vector<int>>& seg_trees, const int range_start, const int range_end) {
    vector<int> answer= {MAX_LIMIT, MIN_LIMIT};
    for (int i = 0; i < 2; ++i) {
        int stt = range_start|seg_trees[i].size()>>1;
        int end = range_end|seg_trees[i].size()>>1;

        while (stt <= end) {
            if (stt & 1) {
                if (i == 0)
                    answer[i] = min(answer[i], seg_trees[i][stt]);
                else
                    answer[i] = max(answer[i], seg_trees[i][stt]);
                stt +=1;
            }
            if (~end & 1) {
                if (i == 0)
                    answer[i] = min(answer[i], seg_trees[i][end]);
                else
                    answer[i] = max(answer[i], seg_trees[i][end]);
                end -= 1;
            }
            stt >>= 1;
            end >>= 1;
        }
    }
    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i) cin >> nums[i];
    vector<vector<int>> seg_trees = make_seg_trees(nums);

    vector<vector<int>> queries(M, vector<int>(2));
    for (int i = 0 ; i < M; ++i) {
        cin >> queries[i][0] >> queries[i][1];
        vector<int> answer = get_range_min_and_max(seg_trees, queries[i][0]-1, queries[i][1]-1);
        cout << answer[0] << ' ' << answer[1] << '\n';
    }

    return 0;
}