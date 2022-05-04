import sys
from collections import deque

input = sys.stdin.readline
N, M, K = map(int, input().split())

board = []
for _ in range(N):
    board.append([int(i) for i in input().rstrip()])

MAX_DIST = 1_000_001

dist = [[[MAX_DIST for _ in range(K+1)] for _ in range(M)] for _ in range(N)]
for i in range(K+1):
    dist[0][0][i] = 1

night = deque([])
day = deque([(0, 0, K)])

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

while len(night) > 0 or len(day) > 0:
    while len(day) > 0:
        y, x, k = day.popleft()
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < N and -1 < b < M:
                # 벽이 없고, 방문하지 않은 경우
                if board[a][b] == 0 and dist[a][b][k] == MAX_DIST:
                    dist[a][b][k] = dist[y][x][k] + 1
                    night.append((a, b, k))
                # 벽이 있는 경우, k 가 0보다 큰지 확인하고, 벽 부수기
                elif board[a][b] == 1 and k > 0 and dist[a][b][k-1] == MAX_DIST:
                    dist[a][b][k-1] = dist[y][x][k] + 1
                    night.append((a, b, k-1))
    # night는 스스로 추가할 수 도 있기 때문에 처음에 횟수를 정하고 수행한다.
    for _ in range(len(night)):
        y, x, k = night.popleft()
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < N and -1 < b < M:
                # 벽이 없고, 방문하지 않은 경우
                if board[a][b] == 0 and dist[a][b][k] == MAX_DIST:
                    dist[a][b][k] = dist[y][x][k] + 1
                    day.append((a, b, k))
                # 벽이 있는 경우, k 가 0보다 큰지 확인하고, 벽 부수기
                elif board[a][b] == 1 and k > 0 and dist[a][b][k-1] == MAX_DIST:
                    dist[a][b][k-1] = dist[y][x][k] + 2
                    night.append((a, b, k-1))


ok = False
for i in range(K+1):
    if dist[N-1][M-1][i] != MAX_DIST:
        ok = True
        break

answer = min(dist[N-1][M-1]) if ok else -1
print(answer)
