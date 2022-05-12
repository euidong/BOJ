import sys
input = sys.stdin.readline

N, M = map(int, input().split())

board = []
cache = []
for i in range(N):
    board.append([int(k) for k in input().split()])
    cache.append([0] * M)

cache[0][0] = board[0][0]
for i in range(1, N):
    cache[i][0] = cache[i-1][0] + board[i][0]
for j in range(1, M):
    cache[0][j] = cache[0][j-1] + board[0][j]

for i in range(1, N):
    for j in range(1, M):
        cache[i][j] = board[i][j] + max([
            cache[i-1][j-1],
            cache[i-1][j],
            cache[i][j-1]
        ])

print(cache[i][j])
