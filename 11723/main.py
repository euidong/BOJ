import sys

M = int(input())

S = [False] * 21
for _ in range(M):
    cmd = sys.stdin.readline().split()
    op = cmd[0]
    if op == 'all':
        S = [True] * 21
        continue
    elif op == 'empty':
        S = [False] * 21
        continue
    num = int(cmd[1])
    if op == 'add':
        S[num] = True
    elif op == 'remove':
        S[num] = False
    elif op == 'check':
        if S[num]:
            print(1)
        else:
            print(0)
    elif op == 'toggle':
        S[num] = not S[num]
