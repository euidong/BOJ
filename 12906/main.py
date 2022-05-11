from collections import deque
import sys
input = sys.stdin.readline


def is_finish(sticks):
    is_same = True
    for i in range(3):
        for v in sticks[i]:
            if (i == 0 and v != 'A') or (i == 1 and v != 'B') or (i == 2 and v != 'C'):
                is_same = False
                break
        if not is_same:
            break
    return is_same


sticks = []
for _ in range(3):
    line = input()
    if line[0] != '0':
        _, st = line.split()
        sticks.append([i for i in st])
    else:
        sticks.append([])

if is_finish(sticks):
    print(0)
    sys.exit()

curr = ' '.join([''.join(stick) for stick in sticks])
visited = {}
visited[curr] = True

q = deque([(sticks, 0)])

while len(q) > 0:
    sticks, depth = q.popleft()
    for i in range(3):
        if len(sticks[i]) == 0:
            continue
        for j in 1, 2:
            temp = [stick[:] for stick in sticks]
            v = temp[i].pop()
            temp[(i + j) % 3].append(v)
            next = ' '.join([''.join(stick) for stick in temp])
            if next not in visited:
                visited[next] = True
                if is_finish(temp):
                    print(depth + 1)
                    sys.exit()
                q.append((temp, depth + 1))
