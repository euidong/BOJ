import sys
input = sys.stdin.readline

N, K = map(int, input().split())
items = []
w_acc = [0] * N
v_acc = [0] * N
for i in range(N):
    items.append([int(k) for k in input().split()])

items = sorted(items, key=lambda x: x[0])
for i in range(N):
    w_acc[i] = w_acc[i-1] + items[i][0]
    v_acc[i] = v_acc[i-1] + items[i][1]

cache = [[0 for _ in range(K+1)] for _ in range(N)]

for i in range(N):
    for j in range(w_acc[i], K+1):
        cache[i][j] = v_acc[i]

for i in range(1, N):
    for j in range(K+1):
        if j >= items[i][0]:
            cache[i][j] = max(cache[i-1][j], cache[i-1]
                              [j-items[i][0]] + items[i][1])
        else:
            cache[i][j] = cache[i-1][j]

print(cache[N-1][K])
