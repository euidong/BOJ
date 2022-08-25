import sys

input = sys.stdin.readline

str1 = input().rstrip()
str2 = input().rstrip()

cache = [[ -1 for _ in range(len(str2))] for _ in range(len(str1))]

for i in range(len(str1)):
    for j in range(len(str2)):
        cache[i][j] = 1 if str1[i] == str2[j] else 0


answer = 0
for i in range(len(str1)):
    max_len = 0
    cur_stk = 0
    for j in range(len(str2)):
        if i+j == len(str1):
            break
        if cache[i+j][j] == 1:
            cur_stk += 1
        else:
            cur_stk = 0
        max_len = max([max_len, cur_stk])
    answer = max([max_len, answer])

for i in range(len(str2)):
    max_len = 0
    cur_stk = 0
    for j in range(len(str1)):
        if i+j == len(str2):
            break
        if cache[j][i+j] == 1:
            cur_stk += 1
        else:
            cur_stk = 0
        max_len = max([max_len, cur_stk])
    answer = max([max_len, answer])

print(answer)