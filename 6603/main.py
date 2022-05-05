def solve(remain, cur=[]):
    if len(cur) == 6:
        print(' '.join([str(i) for i in cur]))
        return
    for idx in range(len(remain)):
        solve(remain[idx+1:], cur + [remain[idx]])


cnt = 0
while True:
    S = [int(i) for i in input().split()]
    if S[0] == 0:
        break
    else:
        if cnt != 0:
            print()
        S.pop(0)
    solve(S)
    cnt += 1
