import sys
input = sys.stdin.readline
sys.setrecursionlimit(10000)

N = int(input())

board = []
for _ in range(N):
    board.append(input().rstrip())


dy = [-1, -1, 0, 1, 1, 0]
dx = [0, 1, 1, 0, -1, -1]

parent = [[(-1, -1) for _ in range(N)] for _ in range(N)]
visited = [[False for _ in range(N)] for _ in range(N)]

answer = [0]


def dfs(y, x, prevY=-1, prevX=-1):
    visited[y][x] = True
    parent[y][x] = (prevY, prevX)
    for i in range(len(dx)):
        a = y + dy[i]
        b = x + dx[i]
        if prevY == a and prevX == b:
            continue
        if -1 < a < N and -1 < b < N and board[a][b] == "X":
            answer[0] = 2
            if visited[a][b]:
                cnt = 0
                cursorY = y
                cursorX = x
                while cursorY != a or cursorX != b:
                    if cursorY == -1 and cursorX == -1:
                        cnt = 1
                        break
                    cursorY, cursorX = parent[cursorY][cursorX]
                    cnt += 1
                if cnt % 2 == 0:
                    print(3)
                    exit(0)
            else:
                dfs(a, b, y, x)


for i in range(N):
    for j in range(N):
        if board[i][j] == "X" and not visited[i][j]:
            answer[0] = 1 if answer[0] == 0 else answer[0]
            dfs(i, j)

print(answer[0])
