import sys
input = sys.stdin.readline
sys.setrecursionlimit(1_000_000)
N, M = map(int, input().split())

board = []
for _ in range(N):
    board.append([int(i) for i in input().rstrip()])
answer = [line[:] for line in board]

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

# color is not available 0, 1

palette = {}


def dfs(y, x, color):
    cnt = 1
    board[y][x] = color
    for i in range(4):
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < N and -1 < b < M and board[a][b] == 0:
            cnt += dfs(a, b, color)
    return cnt % 10


def dfsAll():
    color = -1
    for i in range(N):
        for j in range(M):
            if board[i][j] == 0:
                palette.update({color: dfs(i, j, color)})
                color -= 1


dfsAll()

for i in range(N):
    for j in range(M):
        if answer[i][j] == 1:
            cnt = 1
            colors = {}
            for k in range(4):
                a = i + dy[k]
                b = j + dx[k]
                if -1 < a < N and -1 < b < M and board[a][b] != 1 and colors.get(board[a][b]) == None:
                    colors.update({board[a][b]: palette.get(board[a][b])})
                    cnt += palette.get(board[a][b])
            answer[i][j] = cnt % 10

for line in answer:
    print(''.join([str(i) for i in line]))
