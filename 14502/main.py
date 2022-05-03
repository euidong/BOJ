import sys
input = sys.stdin.readline

N, M = map(int, input().split())
board = []
not_wall_area = N * M
virus_locs = []
for idx in range(N):
    board.append([int(i) for i in input().split()])
    for j in range(M):
        if board[idx][j] == 1:
            not_wall_area -= 1
        elif board[idx][j] == 2:
            virus_locs.append((idx, j))


dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def get_safe_area(board, virus_locs):
    safe_area = not_wall_area - 3
    q = virus_locs[:]
    visited = [[False for _ in range(M)] for _ in range(N)]
    for y, x in virus_locs:
        visited[y][x] = True
        safe_area -= 1

    while len(q) > 0:
        y, x = q.pop(0)
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < N and -1 < b < M and board[a][b] != 1 and not visited[a][b]:
                visited[a][b] = True
                safe_area -= 1
                q.append((a, b))

    return safe_area


answer = 0


def solve(prevY=-1, prevX=-1, remain_wall_cnt=3):
    if remain_wall_cnt == 0:
        global answer
        answer = max([answer, get_safe_area(board, virus_locs)])
        return
    if prevY != -1 and prevX != M - 1:
        for j in range(prevX + 1, M):
            if board[prevY][j] == 0:
                board[prevY][j] = 1
                solve(prevY, j, remain_wall_cnt - 1)
                board[prevY][j] = 0
    for i in range(prevY + 1, N):
        for j in range(M):
            if board[i][j] == 0:
                board[i][j] = 1
                solve(i, j, remain_wall_cnt - 1)
                board[i][j] = 0


solve()

print(answer)
