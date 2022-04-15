import sys

N, K = [int(i) for i in sys.stdin.readline().split()]

comb = [[0 for _ in range(N+1)] for _ in range(N+K)]
comb[0][0] = 0
comb[1][0] = 1
comb[1][1] = 1

for i in range(N+1):
    comb[i][0] = 1
    comb[i][i] = 1

for i in range(2, N+K):
    for j in range(1, i):
        if j > N:
            break
        comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % 1_000_000_000

answer = 0

for i in range(N):
    answer += comb[K+i-1][i]

print(answer)
