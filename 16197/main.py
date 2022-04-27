import sys
input = sys.stdin.readline

N, M = map(int, input().split())

board = []
coins = []
for i in range(N):
    board.append(input().rstrip())
    for j in range(len(board[i])):
        if board[i][j] == 'o':
            board[i] = board[i].replace('o', '.', 1)
            coins.append((i, j))

q = [coins + [0]]

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

while len(q) > 0:
    coin1, coin2, cnt = q.pop(0)
    for i in range(4):
        coin1_y = coin1[0] + dy[i]
        coin1_x = coin1[1] + dx[i]
        coin2_y = coin2[0] + dy[i]
        coin2_x = coin2[1] + dx[i]
        is_coin1_out = True
        is_coin2_out = True
        # coin1만 이동 가능한 경우
        if -1 < coin1_y < N and -1 < coin1_x < M:
            is_coin1_out = False
        if -1 < coin2_y < N and -1 < coin2_x < M:
            is_coin2_out = False
        if is_coin1_out and is_coin2_out:
            continue
        elif is_coin1_out or is_coin2_out:
            print(cnt+1)
            exit(0)
        else:
            if cnt == 10:
                break
            possible = 0
            if board[coin1_y][coin1_x] == '#':
                coin1_y = coin1[0]
                coin1_x = coin1[1]
                possible += 1
            if board[coin2_y][coin2_x] == '#':
                coin2_y = coin2[0]
                coin2_x = coin2[1]
                possible += 1
            if possible < 2:
                q.append([(coin1_y, coin1_x), (coin2_y, coin2_x), cnt+1])

print(-1)
