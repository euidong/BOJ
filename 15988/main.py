import sys
cache = [-1] * 1_000_001
cache[1] = 1
cache[2] = 2
cache[3] = 4
for i in range(4, len(cache)):
    cache[i] = (cache[i - 1] + cache[i - 2] + cache[i - 3]) % 1_000_000_009

T = int(sys.stdin.readline())

for _ in range(T):
    n = int(sys.stdin.readline())
    print(cache[n])
