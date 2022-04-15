import sys
N = int(sys.stdin.readline())
S = [int(i) for i in sys.stdin.readline().split()]

cache = [0] * N
cache[0] = S[0]

for i in range(1, N):
    if cache[i-1] > 0:
        cache[i] = cache[i-1] + S[i]
    else:
        cache[i] = S[i]

print(max(cache))
