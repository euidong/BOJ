# memory : 1_000 * 3 * 4 bytes
# time : O(n)

import sys

N = int(sys.stdin.readline())
cost = []
for _ in range(N):
    cost.append([int(i) for i in sys.stdin.readline().split()])

cache = [[0 for _ in range(3)] for _ in range(N)]
cache[0][0] = cost[0][0]
cache[0][1] = cost[0][1]
cache[0][2] = cost[0][2]
for i in range(N):
    for j in range(3):
        cache[i][j] = cost[i][j] + min([cache[i-1][j-1], cache[i-1][j-2]])

print(min(cache[N-1]))
