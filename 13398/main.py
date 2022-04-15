import sys
N = int(sys.stdin.readline())
A = [int(i) for i in sys.stdin.readline().split()]
cache = [[-100_000_000 for _ in range(2)] for _ in range(N)]

if N == 1:
    print(A[0])
else:
    cache[0][0] = A[0]
    cache[1][0] = A[0] + A[1] if A[0] > 0 else A[1]
    cache[1][1] = A[0] if A[0] > A[1] else A[1]

    for i in range(2, N):
        cache[i][0] = cache[i-1][0] + A[i] if cache[i-1][0] > 0 else A[i]
        cache[i][1] = max([cache[i-1][1], cache[i-2][0]]) + A[i]

    print(max(map(max, cache)))
