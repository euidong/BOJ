import sys
input = sys.stdin.readline

N = int(input())
r1, c1, r2, c2 = map(int, input().split())

dy = [-2, 0, 2, 2, 0, -2]
dx = [1, 2, 1, -1, -2, -1]

visited = [[False for _ in range(N)] for _ in range(N)]

q = [(r1, c1, 0)]
visited[r1][c1] = True

if r1 == r2 and c1 == c2:
    print(0)
else:
    while len(q) > 0:
        y, x, cnt = q.pop(0)
        for i in range(6):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < N and -1 < b < N and not visited[a][b]:
                visited[a][b] = True
                if a == r2 and b == c2:
                    print(cnt + 1)
                    sys.exit()
                q.append((a, b, cnt + 1))
    print(-1)
