from collections import deque
import sys
input = sys.stdin.readline

N, M = map(int, input().split())

board = []
virus_points = []
for i in range(N):
    board.append([int(k) for k in input().split()])
    for j in range(N):
        if board[i][j] == 2:
            virus_points.append((i, j))

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

answer = 1000


def bfs(list):
    visited = [[False for _ in range(N)] for _ in range(N)]
    for (y, x), _ in list:
        visited[y][x] = True
    q = deque(list)
    while len(q) > 0:
        (y, x), depth = q.popleft()
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < N and -1 < b < N and board[a][b] != 1 and not visited[a][b]:
                visited[a][b] = True
                q.append(((a, b), depth + 1))
    # 모두 다 방문했는지 확인
    ok = True
    for i in range(N):
        for j in range(N):
            if not visited[i][j] and board[i][j] != 1:
                ok = False
                break
        if not ok:
            break
    if not ok:
        return -1
    else:
        return depth


def comb(virus_points, selected=[]):
    if len(selected) == M:
        global answer
        result = bfs(selected)
        if result != -1:
            answer = min(answer, result)
    for i in range(len(virus_points)):
        comb(virus_points[i+1:], selected + [(virus_points[i], 0)])


comb(virus_points)

print(-1 if answer == 1000 else answer)
