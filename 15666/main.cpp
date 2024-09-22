#include <iostream>
#include <vector>

using namespace std;

void print_all_combination(vector<int>& nums, const int r, const int prev_num, vector<int>& acc)
{
    for (int i = prev_num; i < 10001; ++i)
    {
        if (nums[i] > 0)
        {
            if (r == 1)
            {
                for (int j = 0; j < acc.size(); ++j)
                {
                    cout << acc[j] << ' ';
                }
                cout << i << '\n';
            } else
            {
                acc.push_back(i);
                print_all_combination(nums, r-1, i, acc);
                acc.pop_back();
            }
        }
    }
}

void solution(const int N, const int M, vector<int>& nums)
{
    vector<int> acc;
    print_all_combination(nums, M, 0, acc);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M; cin >> N >> M;
    vector<int> nums(10001, 0);
    int num;
    for (int i = 0; i < N; ++i)
    {
        cin >> num;
        nums[num]++;
    }
    solution(N, M, nums);
    return 0;
}