from collections import deque
import sys
N = int(input())
scvs = [0, 0, 0]
inp = [int(i) for i in input().split()]
for i in range(len(inp)):
    scvs[i] += inp[i]

is_finished = True
for i in range(3):
    if scvs[i] > 0:
        is_finished = False
if is_finished:
    print(0)
    sys.exit()
visited = [[[False for _ in range(61)] for _ in range(61)]for _ in range(61)]
visited[scvs[0]][scvs[1]][scvs[2]] = True
q = deque([(scvs, 0)])
d = [[9, 3, 1], [9, 1, 3], [3, 9, 1], [1, 9, 3], [1, 3, 9], [3, 1, 9]]
while len(q) > 0:
    curr, depth = q.popleft()
    for i in range(len(d)):
        next = [0, 0, 0]
        next[0] = max([0, curr[0] - d[i][0]])
        next[1] = max([0, curr[1] - d[i][1]])
        next[2] = max([0, curr[2] - d[i][2]])
        next = sorted(next)
        is_finished = True
        if not visited[next[0]][next[1]][next[2]]:
            visited[next[0]][next[1]][next[2]] = True
            for k in range(3):
                if next[k] > 0:
                    is_finished = False
                    break
            if is_finished:
                print(depth + 1)
                sys.exit()
            q.append((next, depth + 1))
