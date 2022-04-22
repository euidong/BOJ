N, K = [int(i) for i in input().split()]

MAX_DIST = 100_001
visited = [False] * MAX_DIST


def go_teleport(cur, que, cnt, target=K):
    while cur < MAX_DIST and not visited[cur]:
        if cur == target:
            return True
        visited[cur] = True
        que.append((cur, cnt))
        cur *= 2
    return False


q = [(N, 0)]

while len(q) > 0:
    cur, cnt = q.pop(0)
    if cur == K:
        print(cnt)
        break
    if go_teleport(cur*2, q, cnt):
        print(cnt)
        break
    if cur + 1 < MAX_DIST and not visited[cur+1]:
        visited[cur+1] = True
        q.append((cur + 1, cnt + 1))
    if cur > 0 and not visited[cur-1]:
        visited[cur - 1] = True
        q.append((cur - 1, cnt + 1))
