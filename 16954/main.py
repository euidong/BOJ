import sys
from collections import deque
input = sys.stdin.readline

N = 8
board = []
for _ in range(N):
    board.append(input().rstrip())

start = (7, 0)
end = (0, 7)

q = deque()
q.append((start, 0))

ok = False

dy = [-1, -1, -1, 0, 0, 0, 1, 1, 1]
dx = [-1, 0, 1, -1, 0, 1, -1, 0, 1]

visited = [[[False for _ in range(N+1)] for _ in range(N)] for _ in range(N)]
visited[7][0][0] = True
while len(q) > 0:
    curr, depth = q.popleft()
    if curr == 8:
        ok = True
        break
    for i in range(9):
        y = curr[0] + dy[i]
        x = curr[1] + dx[i]
        if -1 < y < N and -1 < x < N and not visited[y][x][depth+1]:

            visited[y][x][depth+1] = visited
            # 현재 벽이 있는지 확인
            if y-depth > -1 and board[y-depth][x] == '#':
                continue
            # 다음 차례에 벽이 있는지 확인
            if y-depth > 0 and board[y-depth-1][x] == '#':
                continue
            if depth == 7:
                print(1)
                sys.exit()
            next = (y, x)
            q.append((next, depth + 1))

print(0)
