import sys
input = sys.stdin.readline

s1 = input().rstrip()
s2 = input().rstrip()

cache = [['' for _ in range(len(s2))] for _ in range(len(s1))]

cache[0][0] = s1[0] if s1[0] == s2[0] else ''
for i in range(1, len(s1)):
    if cache[i-1][0] != '':
        cache[i][0] = cache[i-1][0]
    elif s1[i] == s2[0]:
        cache[i][0] = s2[0]
    else:
        cache[i][0] = ''
for i in range(1, len(s2)):
    if cache[0][i-1] != '':
        cache[0][i] = cache[0][i-1]
    elif s1[0] == s2[i]:
        cache[0][i] = s1[0]
    else:
        cache[0][i] = ''

for i in range(1, len(s1)):
    for j in range(1, len(s2)):
        is_same = False
        if s1[i] == s2[j]:
            is_same = True
        cand = [cache[i-1][j], cache[i][j-1],
                cache[i-1][j-1] + s1[i] if is_same else '']
        filter = [len(cache[i-1][j]), len(cache[i][j-1]),
                  len(cache[i-1][j-1]) + 1 if is_same else 0]
        cache[i][j] = cand[filter.index(max(filter))]


print(len(cache[-1][-1]))
print(cache[-1][-1])
