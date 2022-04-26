import sys
input = sys.stdin.readline

board = [[] for _ in range(3)]

for i in range(len(board)):
    for _ in range(6):
        board[i].append([int(i) for i in input().split()])


answer = []
dice = []

dy = [-1, 0, 1, 0]
dx = [0, 1, 0, -1]

# 북/동/남/서
rotate = [
    [None],
    [5, 3, 2, 4],
    [1, 3, 6, 4],
    [5, 6, 2, 1],
    [5, 1, 2, 6],
    [6, 3, 1, 4],
    [2, 3, 5, 4]
]


def dfs(d_idx, b_idx):
    y, x, num, north = dice[d_idx]
    for i in range(4):
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < 6 and -1 < b < 6 and board[b_idx][a][b] == 1:
            board[b_idx][a][b] = -1
            north_idx = rotate[num].index(north)
            direction = (i + north_idx) % 4
            target = rotate[num][direction]
            if i == 2:
                dice.append((a, b, target, num))
            else:
                dice.append((a, b, target, north))
            dfs(len(dice)-1, b_idx)


for b_idx in range(3):
    dice = []
    done = False
    for i in range(6):
        for j in range(6):
            if board[b_idx][i][j] == 1:
                board[b_idx][i][j] = -1
                dice.append((i, j, 1, 5))
                dfs(0, b_idx)
                done = True
                break
        if done:
            break
    test = set()
    for d in dice:
        test.add(d[2])
    answer.append("yes" if len(test) == 6 else "no")

for i in range(3):
    print(answer[i])
