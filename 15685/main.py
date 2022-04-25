import sys
input = sys.stdin.readline

N = int(input())
curves = []
for _ in range(N):
    curves.append([int(i) for i in input().split()])

board = [[0 for _ in range(101)] for _ in range(101)]


dy = [0, -1, 0, 1]
dx = [1, 0, -1, 0]


def dragon_curve(y, x, d, g):
    if g == 0:
        return [(y, x, None), (y+dy[d], x+dx[d], d)]
    if g == 1:
        temp = (y+dy[d], x+dx[d], d)
        next_d = (d+1) % 4
        return [(y, x, None), temp, (temp[0] + dy[next_d], temp[1] + dx[next_d], next_d)]
    prev = dragon_curve(y, x, d, g-1)
    now = prev[:]
    for idx in range(1, len(prev)):
        _,  _, d = prev[idx]
        if idx <= len(prev) // 2:
            d = (d + 2) % 4
        y, x, _ = now[-1]
        a = y + dy[d]
        b = x + dx[d]
        now.append((a, b, d))
    return now


for curve in curves:
    x, y, d, g = curve
    dc = dragon_curve(y, x, d, g)
    for dot in dc:
        y, x, _ = dot
        board[y][x] += 1

dy = [0, 1, 0, 1]
dx = [0, 0, 1, 1]

answer = 0
for i in range(100):
    for j in range(100):
        ok = True
        for k in range(4):
            y = i + dy[k]
            x = j + dx[k]
            if board[y][x] == 0:
                ok = False
                break
        if ok:
            answer += 1

print(answer)
