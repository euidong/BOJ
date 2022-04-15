N, M = [int(i) for i in input().split()]
adj = []
for _ in range(M):
    A, B, C = [int(i) for i in input().split()]
    adj.append((A, B, C))

BIG_NUM = 5000000
dists = [BIG_NUM] * (N + 1)
dists[1] = 0


def bellmanFord():
    for cnt in range(1, N + 1):
        for (start, end, dist) in adj:
            if dists[start] != BIG_NUM and dists[end] > dists[start] + dist:
                if cnt == N:
                    return False
                dists[end] = dists[start] + dist
    return True


if not bellmanFord():
    print(-1)
else:
    for idx in range(2, N+1):
        if dists[idx] == BIG_NUM:
            print(-1)
        else:
            print(dists[idx])
