# limited by maximum recursive call stack
from math import sqrt
MAX_VAL = 100_000

N = int(input())

cache = [-1] * (N + 1)
cache[1] = 1


def min_sum_sq(i):
    if cache[i] != -1:
        return cache[i]
    if sqrt(i).is_integer():
        cache[i] = 1
    else:
        min_val = MAX_VAL
        for k in range(1, i//2 + 1):
            now = min_sum_sq(k) + min_sum_sq(i-k)
            if min_val > now:
                min_val = now
        cache[i] = min_val
    return cache[i]


print(min_sum_sq(N))
