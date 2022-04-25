import sys
input = sys.stdin.readline
N, M = map(int, input().split())

board = []
max_h = 0
for h in range(N):
    board.append([int(i) for i in input().split()])
    max_h = max([max(board[h]), max_h])

dy = [1, 0, -1, 0]
dx = [0, 1, 0, -1]

area = 0

while max_h > 0:
    for i in range(N):
        for j in range(M):
            if board[i][j] >= max_h:
                cnt = 6
                for k in range(4):
                    y = i + dy[k]
                    x = j + dx[k]
                    if -1 < y < N and -1 < x < M and board[y][x] >= max_h:
                        cnt -= 1
                if board[i][j] > max_h:
                    cnt -= 1
                if max_h != 1:
                    cnt -= 1
                area += cnt
    max_h -= 1

print(area)
