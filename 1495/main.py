N, S, M = map(int, input().split())
V = [int(k) for k in input().split()]

cache = [[False for _ in range(M+1)] for _ in range(N)]

p = S + V[0]
m = S - V[0]
if 0 <= p <= M:
    cache[0][p] = True
if 0 <= m <= M:
    cache[0][m] = True

for i in range(1, N):
    for j in range(M+1):
        if cache[i-1][j]:
            p = j + V[i]
            m = j - V[i]
            if 0 <= p <= M:
                cache[i][p] = True
            if 0 <= m <= M:
                cache[i][m] = True

answer = -1
for i in range(M, -1, -1):
    if cache[N-1][i]:
        answer = i
        break
print(answer)
            