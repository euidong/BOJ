import sys
N = int(input())
P = [int(i) for i in sys.stdin.readline().split()]

cache = [-1] * (N + 1)
cache[0] = 0
cache[1] = P[0]

MAX_PRICE = 10_000_001


def solve(x):
    if cache[x] != -1:
        return cache[x]
    min_price = MAX_PRICE
    for idx in range(len(P)):
        next = x - (idx + 1)
        if next > -1:
            min_price = min([min_price, solve(next) + P[idx]])
    cache[x] = min_price
    return cache[x]


print(solve(N))
