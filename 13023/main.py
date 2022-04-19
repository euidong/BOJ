import sys

N, M = [int(i) for i in sys.stdin.readline().split()]
edge = [[] for _ in range(N)]
for _ in range(M):
    a, b = [int(i) for i in sys.stdin.readline().split()]
    edge[a].append(b)
    edge[b].append(a)

dist = [-1] * N
visited = [False] * N


def dfs(cur=0, visited=[False] * N, dist=1):
    if dist > 4:
        return True
    for next in edge[cur]:
        if not visited[next]:
            visited[next] = True
            if dfs(next, visited, dist + 1):
                return True
            visited[next] = False
    return False


ok = False
for i in range(N):
    visited = [False] * N
    visited[i] = True
    if dfs(i, visited):
        ok = True
        break

if ok:
    print(1)
else:
    print(0)
