import sys
input = sys.stdin.readline

T = int(input())
MAX_NUM = 10000
cache = [[-1 for _ in range(4)] for _ in range(MAX_NUM + 1)]
cache[1][1] = 1
cache[1][2] = 0
cache[1][3] = 0
cache[1][0] = 1

cache[2][1] = 1
cache[2][2] = 1
cache[2][3] = 0
cache[2][0] = 2

cache[3][1] = 2
cache[3][2] = 0
cache[3][3] = 1
cache[3][0] = 3

for i in range(4, MAX_NUM + 1):
    cache[i][3] = cache[i-3][3]
    cache[i][2] = cache[i-2][2] + cache[i-2][3]
    cache[i][1] = cache[i-1][1] + cache[i-1][2] + cache[i-1][3]
    cache[i][0] = cache[i][1] + cache[i][2] + cache[i][3]

for _ in range(T):
    print(cache[int(input())][0])
