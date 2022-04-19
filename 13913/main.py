N, K = [int(i) for i in input().split()]

q = [N]

MAX = 100_000
visited = [False] * (MAX + 1)
parent = [-1] * (MAX + 1)
visited[N] = True

while len(q) > 0:
    cur = q.pop(0)
    nexts = [cur * 2, cur + 1, cur - 1]
    ok = False
    for next in nexts:
        if -1 < next <= MAX and not visited[next]:
            visited[next] = True
            parent[next] = cur
            if next == K:
                ok = True
                break
            q.append(next)
    if ok:
        break

idx = K
path = []
while parent[idx] != -1:
    path.append(idx)
    idx = parent[idx]
path.append(N)
print(len(path) - 1)
print(' '.join([str(i) for i in path[::-1]]))
