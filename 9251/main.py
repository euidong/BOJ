import sys
input = sys.stdin.readline

s1 = input().rstrip()
s2 = input().rstrip()

cache = [[-1 for _ in range(len(s2))] for _ in range(len(s1))]

cache[0][0] = 1 if s1[0] == s2[0] else 0
for i in range(1, len(s1)):
    if cache[i-1][0] == 1:
        cache[i][0] = 1
    elif s1[i] == s2[0]:
        cache[i][0] = 1
    else:
        cache[i][0] = 0
for i in range(1, len(s2)):
    if cache[0][i-1] == 1:
        cache[0][i] = 1
    elif s1[0] == s2[i]:
        cache[0][i] = 1
    else:
        cache[0][i] = 0

for i in range(1, len(s1)):
    for j in range(1, len(s2)):
        cache[i][j] = max([cache[i-1][j], cache[i][j-1],
                          cache[i-1][j-1] + 1 if s1[i] == s2[j] else 0])

print(cache[-1][-1])
