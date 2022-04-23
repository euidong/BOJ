import sys
sys.setrecursionlimit(100001)
input = sys.stdin.readline

N = int(input())

adj = [[] for _ in range(N+1)]
for _ in range(N-1):
    a, b = map(int, input().split())
    adj[a].append(b)
    adj[b].append(a)
order = [int(i) for i in input().split()]
visited = [False] * (N+1)


def dfs(curr, ex_next):
    visited[curr] = True
    ok = True
    for next in adj[curr]:
        if not visited[next]:
            ok = False
            if next == ex_next:
                if len(order) == 0:
                    return True
                return dfs(next, order.pop(0))
    return ok


order.pop(0)
print(1 if dfs(1, order.pop(0)) else 0)
