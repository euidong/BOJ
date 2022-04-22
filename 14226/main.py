S = int(input())

MAX_COUNT = 1001
# visited[clip][value] = cnt
visited = [[False for _ in range(MAX_COUNT * 2)] for _ in range(MAX_COUNT * 2)]
visited[0][1] = True
visited[1][1] = True
visited[1][2] = True

q = [(2, 2, 1)]
while len(q) > 0:
    v, cnt, clip = q.pop(0)
    if v == S:
        print(cnt)
        break
    if v < MAX_COUNT and not visited[clip][v+clip]:
        visited[clip][v+clip] = True
        q.append((v+clip, cnt + 1, clip))
    if not visited[clip][v-1]:
        visited[clip][v-1] = True
        q.append((v-1, cnt + 1, clip))
    if not visited[v][v]:
        visited[v][v] = True
        q.append((v, cnt + 1, v))
