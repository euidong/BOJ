#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N; cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; ++i)
        cin >> nums[i];

    sort(nums.begin(), nums.end());

    int cnt = 0;
    for (int target_idx = 0; target_idx < N; ++target_idx)
    {
        int left = 0; int right = N-1;
        while (left != right)
        {
            if (left == target_idx) { left++; continue; }
            if (right == target_idx) { right--; continue; }

            if (nums[target_idx] < nums[left]+nums[right]) right--;
            else if (nums[target_idx] > nums[left]+nums[right]) left++;
            else { cnt++; break; }
        }
    }


    cout << cnt;

    return 0;
}