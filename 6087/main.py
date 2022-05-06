from collections import deque
import sys
input = sys.stdin.readline

W, H = map(int, input().split())

board = []
two_point = []
for i in range(H):
    board.append(input().rstrip())
    for j in range(W):
        if board[i][j] == 'C':
            two_point.append((i, j))

visited = [[False for _ in range(W)] for _ in range(H)]
visited[two_point[0][0]][two_point[0][1]] = True

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

# ((positonY, positionX), direction, depth)
q = deque([(two_point[0][:], i, 0) for i in range(4)])

while len(q) > 0:
    (y, x), direct, depth = q.popleft()
    # 해당 방향으로 쭉이동했을 때 만나는지 확인
    # 이동하는 경로에 거울 하나씩 놓아보기
    a = y + dy[direct]
    b = x + dx[direct]
    while -1 < a < H and -1 < b < W:
        if board[a][b] == '*':
            break
        if not visited[a][b]:
            visited[a][b] = True
            if a == two_point[1][0] and b == two_point[1][1]:
                print(depth)
                sys.exit()
            q.append(((a, b), (direct+1) % 4, depth + 1))
            q.append(((a, b), (direct-1) % 4, depth + 1))
        a += dy[direct]
        b += dx[direct]
