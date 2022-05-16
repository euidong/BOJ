import sys
input = sys.stdin.readline
cache = [0 for _ in range(5001)]
MAX_NUM = 1_000_000_007

cache[2] = 1
cache[4] = 2
cache[6] = 5
for i in range(8, 5001, 2):
    cache[i] = 2 * cache[i-2] + cache[i-4]
    for j in range(6, i, 2):
        cache[i] += cache[j-2] * cache[i-j]
    cache[i] = cache[i] % MAX_NUM

T = int(input())
answer = []
for _ in range(T):
    answer.append(cache[int(input())])
for a in answer:
    print(a)
