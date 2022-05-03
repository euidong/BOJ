import sys
input = sys.stdin.readline

N, M = map(int, input().split())

board = [i for i in range(101)]

for _ in range(N+M):
    x, y = map(int, input().split())
    board[x] = y

q = [(board[1], 0)]
visited = [False] * 101
visited[1] = True

while len(q) > 0:
    curr, cnt = q.pop(0)
    for i in range(1, 7):
        next = board[curr + i]
        if next == 100:
            print(cnt + 1)
            sys.exit()
        if not visited[next]:
            visited[next] = True
            q.append((next, cnt + 1))
