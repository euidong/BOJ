import sys
sys.setrecursionlimit(100000)
T = int(sys.stdin.readline())


def dfs(cur, val, group, adj):
    group[cur] = val
    for next in adj[cur]:
        if group[next] == 0:
            if not dfs(next, -val, group, adj):
                return False
        elif group[next] == group[cur]:
            return False
    return True


for _ in range(T):
    N, M = [int(i) for i in sys.stdin.readline().split()]
    adj = [[] for _ in range(N+1)]
    for _ in range(M):
        a, b = [int(i) for i in sys.stdin.readline().split()]
        adj[a].append(b)
        adj[b].append(a)
    group = [0] * (N+1)
    ok = True
    for v in range(1, N+1):
        if group[v] == 0:
            if not dfs(v, 1, group, adj):
                ok = False
                break
    if ok:
        print("YES")
    else:
        print("NO")
