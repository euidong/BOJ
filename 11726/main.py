N = int(input())

divider = 10_007
cache = [-1] * 1001
cache[1] = 1
cache[2] = 2


def solve(n):
    if cache[n] == -1:
        cache[n] = (solve(n-1) + solve(n-2)) % divider
    return cache[n]


solve(20)  # stack data
print(solve(N))
