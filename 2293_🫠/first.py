import sys
input = sys.stdin.readline

n, k = map(int, input().split())
coins = []
for i in range(n):
    coins.append(int(input()))
coins = sorted(coins)

cache = [0 for _ in range(k+1)]
for i in range(n):
    if coins[i] > k:
        break
    cache[coins[i]] += 1
    for j in range(coins[i]+1, k+1):
        cache[j] += cache[j-coins[i]]

print(cache[k])
