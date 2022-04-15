
N = int(input())

map = []
jewelries = []
impurities = []


def check_area(area1, area2, line):
    check = [0, 0]
    for (y, x) in jewelries:
        if check[0] == 0 and area1[0][0] <= y < area1[1][0] and area1[0][1] <= x < area1[1][1]:
            check[0] = 1
        if check[1] == 0 and area2[0][0] <= y < area2[1][0] and area2[0][1] <= x < area2[1][1]:
            check[1] = 1
    if check[0] and check[1]:
        for (y, x) in jewelries:
            if line[0][0] <= y < line[1][0] and line[0][1] <= x < line[1][1]:
                return False
        return True
    return False


def find_impurities(start, end):
    imps = []
    for (y, x) in impurities:
        if start[0] <= y < end[0] and start[1] <= x < end[1]:
            imps.append((y, x))
    return imps


def find_jewelries(start, end):
    jews = []
    for (y, x) in jewelries:
        if start[0] <= y < end[0] and start[1] <= x < end[1]:
            jews.append((y, x))
    return jews


for i in range(N):
    line = [int(k) for k in input().split(' ')]
    for j in range(N):
        if line[j] == 2:
            jewelries.append((i, j))
        elif line[j] == 1:
            impurities.append((i, j))
    map.append(line)


def solve(start, end, direction):
    imps = find_impurities(start, end)
    if len(imps) == 0:
        if len(find_jewelries(start, end)) > 1:
            return 0
        else:
            return 1
    tot = 0

    for (y, x) in imps:
        if direction != 1:
            if start[1] < x < end[1] - 1:
                left = ((start[0], start[1]), (end[0], x))
                right = ((start[0], x+1), (end[0], end[1]))
                if check_area(left, right, ((start[0], x), (end[0], x+1))):
                    tot += solve(left[0], left[1], 1) * \
                        solve(right[0], right[1], 1)
        if direction != -1:
            if start[0] < y < end[0] - 1:
                up = ((start[0], start[1]), (y, end[1]))
                down = ((y+1, start[1]), (end[0], end[1]))
                if check_area(up, down, ((y, start[1]), (y+1, end[1]))):
                    tot += solve(up[0], up[1], -1) * \
                        solve(down[0], down[1], -1)
    return tot


answer = solve((0, 0), (N, N), 0)
if answer == 0:
    print(-1)
else:
    print(answer)
