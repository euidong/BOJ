import sys
N = int(sys.stdin.readline())

S = [int(i) for i in sys.stdin.readline().split()]

cache = [0] * N
cache[0] = 1
parent = [-1] * N

for i in range(1, N):
    max_idx = i
    for j in range(i):
        if S[j] < S[i] and cache[max_idx] < cache[j]:
            max_idx = j
    if max_idx != i:
        cache[i] = cache[max_idx] + 1
        parent[i] = max_idx
    else:
        cache[i] = 1

max_num = max(cache)
print(max_num)
idx = cache.index(max_num)
seq = []

while parent[idx] != -1:
    seq.append(S[idx])
    idx = parent[idx]
seq.append(S[idx])
seq.reverse()
print(' '.join([str(i) for i in seq]))
