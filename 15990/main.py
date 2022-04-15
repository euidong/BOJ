import sys

DIVIDER = 1_000_000_009
MAX_N = 100_000
cache = [[-1, -1, -1, -1] for _ in range(MAX_N + 1)]

cache[0][0] = 0
cache[0][1] = 0
cache[0][2] = 0
cache[0][3] = 0

cache[1][0] = 1
cache[1][1] = 0
cache[1][2] = 0
cache[1][3] = 1

cache[2][0] = 0
cache[2][1] = 1
cache[2][2] = 0
cache[2][3] = 1

cache[3][0] = 1
cache[3][1] = 1
cache[3][2] = 1
cache[3][3] = 3


def solve(n, k=0):
    if n < 0:
        return 0
    if cache[n][k] != -1:
        return cache[n][k]
    cache[n][k] = (solve(n-(k+1), (k+1) % 3) +
                   solve(n-(k+1), (k+2) % 3)) % DIVIDER
    return cache[n][k]


def answer(n):
    if cache[n][3] != -1:
        return cache[n][3]
    cache[n][3] = (((solve(n, 0) + solve(n, 1)) %
                   DIVIDER) + solve(n, 2)) % DIVIDER
    return cache[n][3]


for i in range(100):
    answer(i * 1000)

N = int(sys.stdin.readline())
for _ in range(N):
    print(answer(int(sys.stdin.readline())))
