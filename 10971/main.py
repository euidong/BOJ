N = int(input())
adj = []
for _ in range(N):
    adj.append([int(i) for i in input().split()])

MAX_DIST = 1000000 * N + 1
min_dist = [MAX_DIST]


def solve(remain, cur, first, tot=0):
    if len(remain) == 0:
        if adj[cur][first] != 0:
            min_dist[0] = min([min_dist[0], tot + adj[cur][first]])
        return
    for idx in range(len(remain)):
        next = remain[idx]
        if adj[cur][next] != 0:
            solve(remain[:idx] + remain[idx+1:],
                  next, first, tot + adj[cur][next])


sample = [i for i in range(N)]
for i in range(N):
    solve(sample[:i] + sample[i+1:], i, i)

print(min_dist[0])
