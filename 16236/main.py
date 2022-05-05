import sys
from collections import deque
input = sys.stdin.readline

N = int(input())
board = []

# shark 위치 / 크기와 먹은 횟수
shark = ()
for i in range(N):
    board.append([int(k) for k in input().split()])
    for j in range(N):
        if board[i][j] == 9:
            shark = ((i, j), 2, 0)

answer = 0


dy = [-1, 0, 0, 1]
dx = [0, -1, 1, 0]

# bfs해서 최단 거리 물고기 찾기


def bfs():
    q = deque()
    pos, size, _ = shark
    q.append((pos, 0))
    visited = [[False for _ in range(N)] for _ in range(N)]
    visited[pos[0]][pos[1]] = True
    found = []
    while len(q) > 0:
        curr, depth = q.popleft()
        if len(found) != 0 and depth >= found[0][1]:
            continue
        for i in range(4):
            y = curr[0] + dy[i]
            x = curr[1] + dx[i]
            if -1 < y < N and -1 < x < N and not visited[y][x]:
                visited[y][x] = True
                if board[y][x] == 0 or board[y][x] == size:
                    if len(found) == 0:
                        q.append(((y, x), depth+1))
                elif board[y][x] < size:
                    found.append(((y, x), depth + 1))
    if len(found) == 0:
        return (None, 0)
    result = found[0]
    for idx in range(1, len(found)):
        cand = found[idx]
        if cand[0][0] < result[0][0]:
            result = cand
        elif cand[0][0] == result[0][0] and cand[0][1] < result[0][1]:
            result = cand
    return result


answer = 0
while True:
    next, time = bfs()
    if time == 0:
        break
    curr, size, cnt = shark
    if cnt == size - 1:
        size += 1
        cnt = 0
    else:
        cnt += 1
    shark = (next, size, cnt)

    board[next[0]][next[1]] = 9
    board[curr[0]][curr[1]] = 0
    answer += time

print(answer)
