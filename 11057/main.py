N = int(input())

cache = [[0 for _ in range(10)] for _ in range(N+1)]

for i in range(10):
    cache[1][i] = 1

for i in range(1, N+1):
    for j in range(10):
        for k in range(j, 10):
            cache[i][j] = (cache[i][j] + cache[i-1][k]) % 10_007

answer = 0
for i in range(10):
    answer = (answer + cache[N][i]) % 10_007
print(answer)
