from collections import deque


EMPTY = 10001
MAX_DIST = 6000 * 10000

N, M = [int(i) for i in input().split(' ')]

graph = [[EMPTY for _ in range(N + 1)] for _ in range(N + 1)]

for _ in range(M):
    a, b, c = [int(i) for i in input().split(' ')]
    if graph[a][b] > c:
        graph[a][b] = c


def bellman_ford(here=1):
    q = [deque(), deque()]

    dist = [MAX_DIST for _ in range(N + 1)]
    dist[here] = 0
    for i in range(1, N + 1):
        if graph[here][i] != EMPTY:
            dist[i] = graph[here][i]
            q[0].append([dist[i], i])

    now_turn = 0
    next_turn = 1
    count = 0
    while len(q[now_turn]) != 0 and count < N:
        top_dist, top_vert = q[now_turn].popleft()

        for i in range(1, N + 1):
            if graph[top_vert][i] != EMPTY:
                if dist[i] > graph[top_vert][i] + top_dist:
                    dist[i] = graph[top_vert][i] + top_dist
                    q[next_turn].append([dist[i], i])

        if len(q[now_turn]) == 0:
            now_turn = next_turn
            next_turn = 0 if now_turn == 1 else 1
            count += 1

    if count == N:
        print(-1)
        return

    for idx in range(2, len(dist)):
        if dist[idx] == MAX_DIST:
            print(-1)
        else:
            print(dist[idx])


bellman_ford()
