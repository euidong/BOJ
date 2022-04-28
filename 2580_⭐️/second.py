import sys

board = []
problems = []
for i in range(9):
    board.append([int(j) for j in input().split()])
    for j in range(9):
        if board[i][j] == 0:
            problems.append((i, j))

target = len(problems)


def dfs(depth=0):
    # 종료 조건 판별
    if depth == target:
        for line in board:
            print(*line)
        sys.exit()
    y, x = problems[depth]
    # 유망성 판단
    # 가로, 세로, 사각형 검색 => 배열 얻기
    poss_bit = [True for _ in range(10)]
    for i in range(9):
        poss_bit[board[y][i]] = False
        poss_bit[board[i][x]] = False
    y_idx = (y//3) * 3
    x_idx = (x//3) * 3
    for i in range(y_idx, y_idx + 3):
        for j in range(x_idx, x_idx + 3):
            poss_bit[board[i][j]] = False
    poss = []
    for i in range(1, 10):
        if poss_bit[i]:
            poss.append(i)
    # 유망하지 않음 (가능성이 없음)
    if len(poss) == 0:
        return

    # 조건 반복
    for pos in poss:
        board[y][x] = pos
        dfs(depth+1)
        board[y][x] = 0


dfs()
