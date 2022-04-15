import sys
N = int(sys.stdin.readline())
A = [int(i) for i in sys.stdin.readline().split()]
cache = [[-1 for _ in range(2)] for _ in range(N)]

for i in range(N):
    up_max_idx = -1
    down_max_idx = -1
    for j in range(i):
        if A[j] < A[i] and cache[up_max_idx][0] < cache[j][0]:
            up_max_idx = j
        if A[j] > A[i] and cache[down_max_idx][1] < cache[j][1]:
            down_max_idx = j
    if cache[up_max_idx][0] > cache[down_max_idx][1]:
        cache[i][1] = cache[up_max_idx][0] + 1
    elif down_max_idx != -1:
        cache[i][1] = cache[down_max_idx][1] + 1
    else:
        cache[i][1] = 1
    if up_max_idx != -1:
        cache[i][0] = cache[up_max_idx][0] + 1
    else:
        cache[i][0] = 1

print(max(map(max, cache)))
