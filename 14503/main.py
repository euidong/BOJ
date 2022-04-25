import sys
input = sys.stdin.readline

N, M = map(int, input().split())
y, x, d = map(int, input().split())

board = []
for _ in range(N):
    board.append([int(i) for i in input().split()])

answer = 0


dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

while True:
    if board[y][x] == 0:
        board[y][x] = -1
        answer += 1
    for i in range(1, 5):
        next_d = (d - i) % 4
        a = y + dy[next_d]
        b = x + dx[next_d]
        if board[a][b] == 0:
            y = a
            x = b
            d = next_d
            break
        if i == 4:
            a = y + dy[d - 2]
            b = x + dx[d - 2]
            if board[a][b] == 1:
                print(answer)
                exit(0)
            else:
                y = a
                x = b
