import sys
input = sys.stdin.readline
sys.setrecursionlimit(10000)

N = int(input())

adj = [[] for _ in range(N+1)]
while True:
    try:
        a, b = map(int, input().split())
        adj[a].append(b)
        adj[b].append(a)
    except (EOFError, ValueError):
        break

visited = [False] * (N+1)
dist = [-1] * (N+1)
cnt = [0]
q = []


def dfs(curr, prev: list = []):
    visited[curr] = True
    cnt[0] += 1
    for next in adj[curr]:
        if len(prev) > 0 and next == prev[-1]:
            continue
        # circle
        if visited[next]:
            in_circle = False
            for v in prev + [curr]:
                if v == next:
                    in_circle = True
                if in_circle:
                    q.append((v, 0))
                    dist[v] = 0
        else:
            dfs(next, prev + [curr])


def dfsAll():
    for i in range(1, N+1):
        if not visited[i]:
            dfs(i)
    while len(q) > 0:
        cur, cnt = q.pop(0)
        for next in adj[cur]:
            if dist[next] == -1:
                dist[next] = cnt + 1
                q.append((next, cnt + 1))
    print(' '.join(map(str, dist[1:])))


dfsAll()
