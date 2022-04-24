import sys
input = sys.stdin.readline

N, L = map(int, input().split())

board = []
for _ in range(N):
    board.append([int(i) for i in input().split()])

answer = 0

# test horizontal
for i in range(N):
    ok = True
    cnt = 1
    prev = board[i][0]
    for j in range(1, N):
        now = board[i][j]
        if prev == now:
            cnt += 1
        elif prev - 1 == now:
            if cnt > -1:
                cnt = -L + 1
            else:
                ok = False
                break
        elif prev + 1 == now:
            if cnt >= L:
                cnt = 1
            else:
                ok = False
                break
        else:
            ok = False
            break
        prev = now
    if ok and cnt > -1:
        answer += 1

for j in range(N):
    ok = True
    cnt = 1
    prev = board[0][j]
    for i in range(1, N):
        now = board[i][j]
        if prev == now:
            cnt += 1
        elif prev - 1 == now:
            if cnt > -1:
                cnt = -L + 1
            else:
                ok = False
                break
        elif prev + 1 == now:
            if cnt >= L:
                cnt = 1
            else:
                ok = False
                break
        else:
            ok = False
            break
        prev = now
    if ok and cnt > -1:
        answer += 1


print(answer)
