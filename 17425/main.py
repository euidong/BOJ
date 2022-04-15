import sys
MAX = 1000001
cache = [1] * MAX
for i in range(2, MAX):
    for j in range(i, MAX, i):
        cache[j] += i
    cache[i] += cache[i-1]

T = int(sys.stdin.readline().rstrip())
for _ in range(T):
    N = int(input())
    sys.stdout.write("{}\n".format(cache[int(sys.stdin.readline().rstrip())]))
