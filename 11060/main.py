import sys
input = sys.stdin.readline

N = int(input())
board = [int(i) for i in input().split()]
cache = [N+1] * N

cache[0] = 0
for i in range(N):
    for j in range(1, board[i] + 1):
        if i + j < N:
            cache[i + j] = min(cache[i+j], cache[i] + 1)

print(cache[N-1] if cache[N-1] != N+1 else -1)
