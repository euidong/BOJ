from posixpath import split
import sys
input = sys.stdin.readline
N, M = [int(i) for i in input().split()]
board = []

# 상 좌 하 우
dx = [0, -1, 0, 1]
dy = [1, 0, -1, 0]

for i in range(N):
    board.append(input().rstrip())


def dfs(hereY, hereX, visited, prevD=-1):
    for i in range(4):
        if i == prevD:
            continue
        nextY = hereY + dy[i]
        nextX = hereX + dx[i]
        if -1 < nextX < M and -1 < nextY < N and \
                board[nextY][nextX] == board[hereY][hereX]:
            if visited[nextY][nextX]:
                return True
            else:
                visited[nextY][nextX] = True
                if dfs(nextY, nextX, visited, (i + 2) % 4):
                    return True
    return False


def dfsAll():
    visited = [[False for _ in range(M)] for _ in range(N)]
    for i in range(N):
        for j in range(M):
            if not visited[i][j]:
                visited[i][j] = True
                if dfs(i, j, visited):
                    return True
    return False


print("Yes" if dfsAll() else "No")
