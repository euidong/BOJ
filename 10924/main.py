import sys
input = sys.stdin.readline
sys.setrecursionlimit(2000)

N = int(input())
seq = [-1] + [int(k) for k in input().split()]
cache = [[-1 for _ in range(N+1)] for _ in range(N+1)]
for i in range(1, N+1):
    cache[i][i] = 1


def is_palindrome(i, j):
    if i > j:
        return 1
    if cache[i][j] == -1:
        if seq[i] == seq[j]:
            cache[i][j] = is_palindrome(i+1, j-1)
        else:
            cache[i][j] = 0
    return cache[i][j]


M = int(input())
result = []
for _ in range(M):
    a, b = map(int, input().split())
    result.append(is_palindrome(a, b))

for r in result:
    print(r)
