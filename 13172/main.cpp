#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const long long DIVIDER = 1000000007;

long long calc_inverse(const long long b)
{
    // 1. b^{-1} = b^{DIVIDER-2} % DIVIDER
    // 2. b^{DIVIDER-2} = b^{2^{x_1}} * b^{2^{x_2}} + ...

    long long b_inv = 1;

    // 2의 거듭제곱 수의 합으로 분해하기
    long long remain = DIVIDER - 2;
    long long miner = (long long)pow(2, 30);
    int idx = 30;
    vector<int> idxs;
    while (remain != 0)
    {
        if (remain >= miner)
        {
            remain -= miner;
            idxs.push_back(idx);
        }
        miner /= 2; idx--;
    }

    // b의 거듭제곱 수 구하기
    vector<long long> b_powers(30);
    b_powers[0] = b;
    for (int i = 1; i < 30; ++i)
        b_powers[i] = (b_powers[i-1] * b_powers[i-1]) % DIVIDER;

    for (const auto idx : idxs)
        b_inv = (b_inv * b_powers[idx]) % DIVIDER;

    return b_inv;
}


long long solution(const int M, const vector<vector<long long>>& NS)
{
    long long sum = 0;
    for (int i = 0; i < M; ++i)
    {
        const long long b = NS[i][0], a = NS[i][1];
        // long long mult = 1;
        // while ((DIVIDER * mult + 1) % b != 0)
        //     mult++;
        // const long long b_1 = (DIVIDER * mult + 1) / b;
        const long long b_inv = calc_inverse(b);

        sum = (sum + (a * b_inv) % DIVIDER) % DIVIDER;
    }
    return sum;
}


int main()
{
    int M; cin >> M;
    vector<vector<long long>> NS(M, vector<long long>(2));
    for (int i = 0; i < M; ++i) cin >> NS[i][0] >> NS[i][1];

    cout << solution(M, NS);

    return 0;
}