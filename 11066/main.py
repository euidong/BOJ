import sys
input = sys.stdin.readline

T = int(input())

for _ in range(T):
    K = int(input())
    files = [int(k) for k in input().split()]
    cache = [[-1 for _ in range(K)] for _ in range(K)]
    acc = [0] * K
    for k in range(K):
        cache[k][k] = 0
        acc[k] = acc[k-1] + files[k]
    for i in range(K-2, -1, -1):
        for j in range(i+1, K):
            min_tot = 5000_0000
            size = acc[j] - acc[i] + files[i]
            for h in range(j-i):
                tot = cache[i][i+h] + cache[i+h+1][j] + size
                if min_tot > tot:
                    min_tot = tot
            cache[i][j] = min_tot
    print(cache[0][K-1])
