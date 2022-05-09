import sys
from collections import deque

input = sys.stdin.readline

M, N = map(int, input().split())

board = []
for _ in range(N):
    board.append([int(k) for k in input().split()])
areas = []
color_board = [[-1 for _ in range(M)] for _ in range(N)]

dy = [0, -1, 0, 1]
dx = [-1, 0, 1, 0]


def dfs(curr, color):
    y, x = curr
    areas[color] += 1
    color_board[y][x] = color
    can_go = [i for i in range(4)]
    temp = board[y][x]
    cnt = 0
    while temp > 0:
        if temp & 1:
            can_go.remove(cnt)
        temp >>= 1
        cnt += 1
    for i in can_go:
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < N and -1 < b < M and color_board[a][b] == -1:
            dfs((a, b), color)


def dfsAll():
    idx = 0
    for i in range(N):
        for j in range(M):
            if color_board[i][j] == -1:
                areas.append(0)
                dfs((i, j), idx)
                idx += 1


dfsAll()

visited = [[False for _ in range(M)] for _ in range(N)]
visited[0][0] = True

q = deque([(0, 0)])
sum_area = 0
while len(q) > 0:
    y, x = q.popleft()
    curr_color = color_board[y][x]
    for i in range(4):
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < N and -1 < b < M and not visited[a][b]:
            visited[a][b] = True
            next_color = color_board[a][b]
            if curr_color != next_color:
                sum_area = max(sum_area, areas[curr_color] + areas[next_color])
            else:
                sum_area = max(sum_area, areas[curr_color])
            q.append((a, b))

print(len(areas))
print(max(areas))
print(sum_area)
