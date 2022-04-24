import sys
input = sys.stdin.readline
sys.setrecursionlimit(100000)

N, M, R = map(int, input().split())
A = []
for _ in range(N):
    A.append([int(i) for i in input().split()])

dy = [1, 0, -1, 0]
dx = [0, 1, 0, -1]

# curr = [y, x]
# max_pos = [y, x]
# min_pos = [y, x]


def rotate(curr, dist, max_pos, min_pos):
    # down
    if curr[0] == min_pos[0] and curr[1] == min_pos[1]:
        y = curr[0] + dist
        x = curr[1]
        if max_pos[0] < y:
            return rotate([max_pos[0], x], y - max_pos[0], max_pos, min_pos)
        else:
            return [y, x]
    # left
    elif curr[0] == min_pos[0]:
        y = curr[0]
        x = curr[1] - dist
        if min_pos[1] > x:
            return rotate([y, min_pos[1]], min_pos[1] - x, max_pos, min_pos)
        else:
            return [y, x]
    # up
    elif curr[1] == max_pos[1]:
        y = curr[0] - dist
        x = curr[1]
        if min_pos[0] > y:
            return rotate([min_pos[0], x], min_pos[0] - y, max_pos, min_pos)
        else:
            return [y, x]
    # right
    elif curr[0] == max_pos[0]:
        y = curr[0]
        x = curr[1] + dist
        if max_pos[1] < x:
            return rotate([y, max_pos[1]], x - max_pos[1], max_pos, min_pos)
        else:
            return [y, x]
    # down
    elif curr[1] == min_pos[1]:
        y = curr[0] + dist
        x = curr[1]
        if max_pos[0] < y:
            return rotate([max_pos[0], x], y - max_pos[0], max_pos, min_pos)
        else:
            return [y, x]


answer = [[-1 for _ in range(M)] for _ in range(N)]
rot = 0
cursor = [0, 0]
start = [0, 0]
end = [N-1, M-1]
while start[0] < end[0] and start[1] < end[1]:
    r = R % ((end[0] + end[1] - start[0] - start[1]) * 2)
    while cursor[0] < end[0] + 1:
        # something
        y, x = rotate(cursor, r, end, start)
        answer[y][x] = A[cursor[0]][cursor[1]]
        cursor[0] += 1
    cursor[0] -= 1
    while cursor[1] < end[1] + 1:
        # someting
        y, x = rotate(cursor, r, end, start)
        answer[y][x] = A[cursor[0]][cursor[1]]
        cursor[1] += 1
    cursor[1] -= 1
    while cursor[0] > start[0] - 1:
        # someting
        y, x = rotate(cursor, r, end, start)
        answer[y][x] = A[cursor[0]][cursor[1]]
        cursor[0] -= 1
    cursor[0] += 1
    while cursor[1] > start[1] - 1:
        # someting
        y, x = rotate(cursor, r, end, start)
        answer[y][x] = A[cursor[0]][cursor[1]]
        cursor[1] -= 1
    rot += 1
    cursor = [rot, rot]
    start = [rot, rot]
    end = [N - 1 - rot, M - 1 - rot]

for line in answer:
    print(' '.join([str(i) for i in line]))
