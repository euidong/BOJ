import sys

T = int(sys.stdin.readline())

dx = [1, 2, 2, 1, -1, -2, -2, -1]
dy = [2, 1, -1, -2, -2, -1, 1, 2]

for i in range(T):
    I = int(sys.stdin.readline())
    startX, startY = [int(i) for i in sys.stdin.readline().split()]
    endX, endY = [int(i) for i in sys.stdin.readline().split()]
    board = [[-1 for _ in range(I)] for _ in range(I)]
    board[startX][startY] = 0
    q = [(startX, startY)]
    while len(q) != 0:
        x, y = q.pop(0)
        for i in range(len(dx)):
            a = x + dx[i]
            b = y + dy[i]
            if -1 < a < I and -1 < b < I and board[a][b] == -1:
                board[a][b] = board[x][y] + 1
                q.append((a, b))
    print(board[endX][endY])
