from math import sqrt
MAX_VAL = 100_000

N = int(input())

cache = [-1] * (N + 1)
cache[0] = 0
cache[1] = 1

for i in range(2, N+1):
    if sqrt(i).is_integer():
        cache[i] = 1
    else:
        min_val = MAX_VAL
        for k in range(1, i//2 + 1):
            now = cache[k] + cache[i-k]
            if min_val > now:
                min_val = now
        cache[i] = min_val

print(cache[N])
