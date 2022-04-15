import sys

N = int(sys.stdin.readline())
P = [int(i) for i in sys.stdin.readline().split()]

cache = [-1] * (N+1)
cache[0] = 0
cache[1] = P[0]


def solve(x):
    if cache[x] != -1:
        return cache[x]
    max_price = -1
    for idx in range(len(P)):
        next = x - (idx + 1)
        if next > -1:
            max_price = max([max_price, solve(next) + P[idx]])
    cache[x] = max_price
    return cache[x]


print(solve(N))
