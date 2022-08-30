import sys

input = sys.stdin.readline

R, C, T = map(int, input().split())

A = []
airCond = []
for i in range(R):
    line = [int(j) for j in input().split()]
    if line[0] == -1:
        airCond.append(i)
    A.append(line)

dy = [-1, 0, 1, 0]
dx = [0, -1, 0, 1]

upper_direc = [(-1, 0), (0, 1), (1, 0), (0, -1)]
under_direc = [(1, 0), (0, 1), (-1, 0), (0, -1)]

while T > 0:
    next_A = [[0 for _ in range(C)] for _ in range(R)]
    next_A[airCond[0]][0] = -1
    next_A[airCond[1]][0] = -1
    for i in range(R):
        for j in range(C):
            if A[i][j] > 0:
                cnt = 0
                adder = A[i][j] // 5
                for k in range(4):
                    y = i + dy[k]
                    x = j + dx[k]
                    if -1 < y < R and -1 < x < C:
                        if (y == airCond[0] or y == airCond[1]) and x == 0:
                            continue
                        next_A[y][x] += adder
                        cnt += 1
                next_A[i][j] += A[i][j] - (adder * cnt)

    curY = airCond[0] - 1
    curX = 0
    for i in range(4):
        direc = upper_direc[i]
        nextY = curY + direc[0]
        nextX = curX + direc[1]
        while -1 < nextY <= airCond[0] and -1 < nextX < C:
            next_A[curY][curX] = next_A[nextY][nextX]
            curY = nextY
            curX = nextX
            nextY = curY + direc[0]
            nextX = curX + direc[1]
    next_A[airCond[0]][0] = -1
    next_A[airCond[0]][1] = 0

    curY = airCond[0] + 1
    curX = 0
    for i in range(4):
        direc = under_direc[i]
        nextY = curY + direc[0]
        nextX = curX + direc[1]
        while airCond[1] <= nextY < R and -1 < nextX < C:
            next_A[curY][curX] = next_A[nextY][nextX]
            curY = nextY
            curX = nextX
            nextY = curY + direc[0]
            nextX = curX + direc[1]
    next_A[airCond[1]][0] = -1
    next_A[airCond[1]][1] = 0

    A = next_A

    T -= 1

answer = 2
for i in range(R):
    for j in range(C):
        answer += A[i][j]
print(answer)
