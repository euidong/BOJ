from collections import deque
import sys
input = sys.stdin.readline

K = int(input())
W, H = map(int, input().split())
board = []
for _ in range(H):
    board.append([int(i) for i in input().split()])

if W == H == 1:
    print(1 if board[0][0] == 1 else 0)
    sys.exit()

monkey_dy = [0, 1, 0, -1]
monkey_dx = [1, 0, -1, 0]

horse_dy = [-2, -1, 1, 2, 2, 1, -1, -2]
horse_dx = [1, 2, 2, 1, -1, -2, -2, -1]

visited = [[[False for _ in range(K+1)] for _ in range(W)] for _ in range(H)]
visited[0][0][K] = True

q = deque([((0, 0), 0, K)])
while len(q) > 0:
    (y, x), depth, k = q.popleft()
    if k > 0:
        for i in range(8):
            a = y + horse_dy[i]
            b = x + horse_dx[i]
            if -1 < a < H and -1 < b < W and board[a][b] != 1 and not visited[a][b][k-1]:
                visited[a][b][k-1] = True
                if a == H-1 and b == W-1:
                    print(depth+1)
                    sys.exit()
                q.append(((a, b), depth + 1, k-1))
    for i in range(4):
        a = y + monkey_dy[i]
        b = x + monkey_dx[i]
        if -1 < a < H and -1 < b < W and board[a][b] != 1 and not visited[a][b][k]:
            visited[a][b][k] = True
            if a == H-1 and b == W-1:
                print(depth+1)
                sys.exit()
            q.append(((a, b), depth + 1, k))

print(-1)
