from collections import deque


size_y, size_x = [int(i) for i in input().split(' ')]

map = [[0 for _ in range(size_y)] for _ in range(size_x)]
visited = [[[0, 0] for _ in range(size_y)] for _ in range(size_x)]
for y in range(size_y):
    data = input()
    for x, d in enumerate(data):
        map[x][y] = int(d)


dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]


def bfs():
    q = deque()
    q.append([0, 0, 1])
    visited[0][0][1] = 1
    while len(q) != 0:
        x, y, wall = q.popleft()
        if x == size_x - 1 and y == size_y - 1:
            return int(visited[x][y][wall])
        for i in range(4):
            a = x + dx[i]
            b = y + dy[i]
            if 0 <= a <= size_x - 1 and 0 <= b <= size_y - 1:
                if visited[a][b][wall] == 0:
                    if map[x][y] == 1 and wall > 0:
                        visited[a][b][wall-1] = visited[x][y][wall] + 1
                        q.append([a, b, wall-1])
                    elif map[x][y] == 0:
                        visited[a][b][wall] = visited[x][y][wall] + 1
                        q.append([a, b, wall])
    return -1


print(bfs())
