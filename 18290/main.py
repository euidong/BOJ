N, M, K = [int(i) for i in input().split()]
board = []
for _ in range(N):
    board.append([int(i) for i in input().split()])


dx = [1, 0]
dy = [0, 1]


def solve(board, y=-1, x=0, cur=0, value=0):
    if cur == K:
        return value
    max_val = -400000
    if y != -1:
        for j in range(x + 1, M):
            if board[y][j] == None:
                continue
            backup = []
            for k in range(2):
                a = y + dy[k]
                b = j + dx[k]
                if 0 <= a < N and 0 <= b < M:
                    backup.append((a, b, board[a][b]))
                    board[a][b] = None
            max_val = max(
                [max_val, solve(board, y, j, cur + 1, value + board[y][j])])
            for a, b, c in backup:
                board[a][b] = c
    for i in range(y + 1, N):
        for j in range(M):
            if board[i][j] == None:
                continue
            backup = []
            for k in range(2):
                a = i + dy[k]
                b = j + dx[k]
                if 0 <= a < N and 0 <= b < M:
                    backup.append((a, b, board[a][b]))
                    board[a][b] = None
            max_val = max(
                [max_val, solve(board, i, j, cur + 1, value + board[i][j])])
            for a, b, c in backup:
                board[a][b] = c
    return max_val


print(solve(board))
