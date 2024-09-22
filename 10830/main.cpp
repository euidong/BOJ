#include <iostream>
#include <vector>

using namespace std;

vector<vector<vector<int>>> cache;

vector<vector<int>> matmul(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    const int N = A.size();
    vector<vector<int>> C(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % 1000;
            }
        }
    }

    return C;
}

vector<vector<int>> dp(const int n)
{
    if (cache[n][0][0] != -1)
        return cache[n];

    return cache[n] = matmul(dp(n - 1), dp(n - 1));
}

pair<int, long long> calc_max_power_of_2(const long long n)
{
    pair<int, long long> power_n_value = make_pair(0, 1);
    while (power_n_value.second <= n)
    {
        power_n_value.first += 1;
        power_n_value.second *= 2;
    }
    power_n_value.first -= 1;
    power_n_value.second /= 2;

    return power_n_value;
}

// 5 = 1 + 2^2

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    // 행렬곱
    int N; long long B; cin >> N >> B;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> A[i][j];

    cache = vector<vector<vector<int>>>(40, vector<vector<int>>(N, vector<int>(N, -1)));

    // B를 2의 제곱수의 곱으로 바꾸기
    vector<int> eles;
    while (B != 0)
    {
        pair<int, long long> power_n_value = calc_max_power_of_2(B);
        B -= power_n_value.second;
        eles.push_back(power_n_value.first);
    }

    vector<vector<int>> answer(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) answer[i][i] = 1;

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cache[0][i][j] = A[i][j];

    for (const auto & ele : eles)
        answer = matmul(answer, dp(ele));

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << answer[i][j] << ' ';
        }
        cout << '\n';
    }

    return 0;
}