#include <iostream>
#include <vector>

#define CACHE_SIZE 1048576 // 1024 * 1024
#define DIVIDER 1000000007

using namespace std;

// cache[k] = cache[k-1] + cache[k-2]

// cache[m] = cache[m - 1] + cache[m - 2]
//            = 2cache[m - 2] + cache[m - 3]
//            = 3cache[m - 3] + 2cache[m - 4]
//            = 5cache[m - 4] + 3cache[m - 5]
//            = 8cache[m - 5] + 5cache[m - 6]
//            = 13cache[m - 6] + 8cache[m - 7]
//            = cache[7]cache[m-6] + cache[6]cache[m-7]
//            = cache[6]cache[m-5] + cache[5]cache[m-6]
//            = cache[3]cache[m-2] + cache[2]cache[m-3]
//            = cache[2]cache[m-1] + cache[1]cache[m-2]
//            = cache[a+1]cache[m-a] + cache[a]cache[m-(a+1)]
//            = cache[m/2]cache[m-(m/2+1)] + cache[m/2+1]cache[m - m/2]

// m = 홀수인경우
// cache[7] = cache[4]cache[7-3] + cache[3]cache[7-4]
// cache[6] = cache[3]cache[6-4] + cache[4]cache[6-3]

// cache[m] = cache[mid+1]cache[mid+1] + cache[mid]cache[mid]
// cache[m-1] = cahce[mid]cache[mid-1] + cache[mid+1]cache[mid]

// m = 짝수인경우
// cache[8] = cache[4]cache[3] + cache[5]cache[4]
// cache[7] = cache[4]cache[4] + cache[3]cache[3]

// cache[m] = cache[mid]cache[mid-1] + cache[mid+1]cache[mid]
// cache[m-1] = cache[mid]cache[mid] + cache[mid-1]cache[mid-1]

// 256 MB -> 4 bytes x 256(2^8) x 1024(2^10) x 256(2^8)
// 안전하게 2^20 정도까지만 할당

int cache[CACHE_SIZE];

vector<long long> fibo(const long long idx)
{
    if (idx < CACHE_SIZE && cache[idx] != -1 && cache[idx-1] != -1)
        return {cache[idx], cache[idx-1]};

    const int long long mid = idx / 2; // fibo(mid-1), fibo(mid+1)은 어떻게 구할 수 있을까?
    auto vs = fibo(mid);
    const long long fibo_mid = vs[0], fibo_mid_minus_1 = vs[1];
    const long long fibo_mid_plus_1 = (fibo_mid + fibo_mid_minus_1) % DIVIDER;

    long long result;
    if (idx % 2 == 0)
        result = (fibo_mid * fibo_mid_minus_1 + fibo_mid_plus_1 * fibo_mid) % DIVIDER;
    else
        result = (fibo_mid * fibo_mid + fibo_mid_plus_1 * fibo_mid_plus_1) % DIVIDER;

    long long result_minus_1;
    if (idx % 2 == 0)
        result_minus_1 = (fibo_mid * fibo_mid + fibo_mid_minus_1 * fibo_mid_minus_1) % DIVIDER;
    else
        result_minus_1 = (fibo_mid * fibo_mid_minus_1 + fibo_mid_plus_1 * fibo_mid) % DIVIDER;

    if (idx < CACHE_SIZE)
        cache[idx] = result;

    return {result, result_minus_1};
}

int main()
{
    long long n; cin >> n;
    // 2의 제곱수 정도의 fibo를 저장해두고, 그 외에는 직접 구해야할 듯?
    // n을 2의 제곱수의 합으로 분해

    // 2의 제곱 수의 fibo을 계산
    for (int & i : cache) i = -1;

    cache[0] = 0;
    cache[1] = 1;
    cache[2] = 1;

    cout << fibo(n)[0];

    return 0;
}