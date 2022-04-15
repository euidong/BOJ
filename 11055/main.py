import sys
N = int(sys.stdin.readline())
A = [int(i) for i in sys.stdin.readline().split()]
cache = [-1] * N

for i in range(N):
    max_idx = -1
    for j in range(0, i):
        if A[j] < A[i] and cache[max_idx] < cache[j]:
            max_idx = j
    if max_idx != -1:
        cache[i] = cache[max_idx] + A[i]
    else:
        cache[i] = A[i]

print(max(cache))
