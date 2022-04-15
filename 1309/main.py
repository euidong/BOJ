N = int(input())

cache = [[0 for _ in range(2)] for _ in range(N+1)]

cache[1][0] = 3
cache[1][1] = 2
for i in range(2, N+1):
    cache[i][0] = (cache[i-1][0] + 2 * cache[i-1][1]) % 9901
    cache[i][1] = (cache[i-1][0] + cache[i-1][1]) % 9901

print(cache[N][0])
