

from collections import deque

map = []
visited = []

[size_y, size_x] = [int(i) for i in input().split(' ')]

for _ in range(size_y):
    data = input()
    map.append(data)
    visited.append([[0, 0] for _ in data])


dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]


def bfs():
    q = deque()
    q.append([0, 0, 1])
    visited[0][0][1] = 1
    while len(q) != 0:
        i, j, wall = q.popleft()
        if i == size_x - 1 and j == size_y - 1:
            return visited[j][i][wall]
        for k in range(4):
            a = i+dx[k]
            b = j+dy[k]
            if 0 <= a < size_x and 0 <= b < size_y:
                if wall == 1 and map[b][a] == '1':
                    visited[b][a][0] = visited[j][i][1] + 1
                    q.append([a, b, 0])
                elif map[b][a] == '0' and visited[b][a][wall] == 0:
                    visited[b][a][wall] = visited[j][i][wall] + 1
                    q.append([a, b, wall])
    return -1


print(bfs())
