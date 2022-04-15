N = int(input())

cache = [[0 for _ in range(2)] for _ in range(N+1)]

if N == 1:
    print(0)
else:
    cache[2][0] = 3
    cache[2][1] = 4
    for i in range(4, N+1, 2):
        cache[i][0] = cache[i-2][0] + 2 * cache[i-2][1]
        cache[i][1] = cache[i-2][1] + cache[i][0]

    print(cache[N][0])
