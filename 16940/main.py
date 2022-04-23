import sys
input = sys.stdin.readline

N = int(input())
adj = [[] for _ in range(N+1)]
for _ in range(N-1):
    a, b = map(int, input().split())
    adj[a].append(b)
    adj[b].append(a)

order = [int(i) for i in input().split()]

# pos, depth
visited = [False] * (N+1)
visited[1] = True
order.pop(0)
q = [1]

ok = True
while len(q) > 0:
    curr = q.pop(0)
    temp = set()
    real = set()
    for next in adj[curr]:
        if not visited[next]:
            visited[next] = True
            temp.add(next)
            real.add(order.pop(0))
    if temp != set(real):
        ok = False
        break
    q += real

print(1 if ok else 0)
