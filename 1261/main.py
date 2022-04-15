from queue import PriorityQueue

map = []
visited = []
dx = [1, 0, -1, 0]
dy = [0, 1, 0, -1]

X, Y = [int(i) for i in input().split(' ')]

visited = [[-1 for _ in range(X)] for _ in range(Y)]
for _ in range(Y):
    map.append([int(i) for i in input()])

q = PriorityQueue()
q.put([0, 0, 0])
visited[0][0] = 0
while not q.empty():
    wall, y, x = q.get()
    if X - 1 == x and Y - 1 == y:
        print(wall)
        break
    wall += map[y][x]
    for i in range(len(dx)):
        b = y + dy[i]
        a = x + dx[i]
        if -1 < b < Y and -1 < a < X:
            if visited[b][a] == -1 or visited[b][a] > wall:
                visited[b][a] = wall
                q.put([wall, b, a])
