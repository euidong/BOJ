import sys
n = int(sys.stdin.readline())
amount = [-1]
for _ in range(n):
    amount.append(int(sys.stdin.readline()))
if n == 1:
    print(amount[1])
else:
    cache = [[0 for _ in range(3)] for _ in range(n+1)]

    cache[1][0] = 0
    cache[1][1] = amount[1]
    cache[2][0] = amount[1]
    cache[2][1] = amount[2]
    cache[2][2] = amount[1] + amount[2]

    for i in range(3, n+1):
        cache[i][0] = max(cache[i-1])
        cache[i][1] = cache[i-1][0] + amount[i]
        cache[i][2] = cache[i-1][1] + amount[i]

    print(max(cache[n]))
