import sys
input = sys.stdin.readline

n, k = map(int, input().split())
coins = set()
for _ in range(n):
    coins.add(int(input()))

coins = list(coins)

cache = [0] * (k+1)

for i in range(k+1):
    for j in range(len(coins)):
        cursor = i - coins[j]
        if -1 < cursor:
            if cursor != 0 and cache[cursor] == 0:
                continue
            if cache[i] == 0:
                cache[i] = cache[cursor] + 1
            else:
                cache[i] = min([cache[i], cache[cursor] + 1])

print(cache[k] if cache[k] != 0 else -1)
