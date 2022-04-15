DIVIDER = 1000000007

N, K = [int(i) for i in input().split(' ')]

if K == 0 or K == N:
    print(1)
else:
    cache = [[0 for _ in range(N + 1)] for _ in range(K + 1)]
    for i in range(0, N + 1):
        cache[0][i] = 1
    for i in range(0, K + 1):
        cache[i][i] = 1
    for j in range(1, K + 1):
        for i in range(2, N + 1):
            cache[j][i] = (cache[j][i - 1] + cache[j - 1][i - 1]) % DIVIDER
    print(cache[K][N])
