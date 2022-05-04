import sys
from collections import deque
input = sys.stdin.readline
N, M, K = map(int, input().split())

MAX_DIST = 1_000_001

board = []
for _ in range(N):
    board.append([int(i) for i in input().rstrip()])

dist = [[[MAX_DIST for _ in range(K+1)] for _ in range(M)] for _ in range(N)]
for i in range(K+1):
    dist[0][0][i] = 1

q = deque([(0, 0, K)])

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

while len(q) > 0:
    y, x, k = q.popleft()
    for i in range(4):
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < N and -1 < b < M:
            # 벽이 아니고, 아직 안들른 경우
            if board[a][b] == 0 and dist[a][b][k] == MAX_DIST:
                dist[a][b][k] = dist[y][x][k] + 1
                q.append((a, b, k))
            # 벽인데, 아직 뚫을 수 있고, 아직 안들른 경우
            elif board[a][b] == 1 and k > 0 and dist[a][b][k-1] == MAX_DIST:
                dist[a][b][k-1] = dist[y][x][k] + 1
                q.append((a, b, k-1))

ok = False
for i in range(K+1):
    if dist[N-1][M-1][i] != MAX_DIST:
        ok = True
        break

answer = min(dist[N-1][M-1]) if ok else -1
print(answer)
