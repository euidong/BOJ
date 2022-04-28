import sys
input = sys.stdin.readline

board = []
blocks = []
empties = []


def get_yidx(v):
    return ord(v) - 65


def gen_block():
    blocks = []
    for i in range(1, 10):
        for j in range(i+1, 10):
            blocks.append((i, j))
    return blocks

# 2차원 배열을 return
# ex
# [[x y]
#  [0 0]] or
# [[x 0]
#  [y 0]]


def get_poss_blks(y, x):
    is_y_end = True if y == 8 or board[y+1][x] != 0 else False
    is_x_end = True if x == 8 or board[y][x+1] != 0 else False
    if is_y_end and is_x_end:
        return []
    poss_me = get_poss(y, x)
    poss_down = [] if is_y_end else get_poss(y+1, x)
    poss_right = [] if is_x_end else get_poss(y, x+1)
    if len(poss_me) == 0:
        return []
    if len(poss_down) == 0 and len(poss_right) == 0:
        return []
    poss_blks = []
    # TODO filtering poss_blk
    for i in poss_me:
        for j in poss_down:
            for idx, block in enumerate(blocks):
                if (block[0] == i and block[1] == j) or (block[0] == j and block[1] == i):
                    poss_blks.append([[i, 0], [j, idx]])
        for j in poss_right:
            for idx, block in enumerate(blocks):
                if (block[0] == i and block[1] == j) or (block[0] == j and block[1] == i):
                    poss_blks.append([[i, j], [0, idx]])

    return poss_blks


def get_poss(y, x):
    poss = [True] * 10
    poss[0] = False
    for i in range(9):
        poss[board[y][i]] = False
        poss[board[i][x]] = False
    y_idx = (y // 3) * 3
    x_idx = (x // 3) * 3
    for i in range(y_idx, y_idx + 3):
        for j in range(x_idx, x_idx + 3):
            poss[board[i][j]] = False
    result = []
    for i in range(1, 10):
        if poss[i]:
            result.append(i)
    return result


def dfs(depth=0):
    if len(empties) == depth:
        return True
    y = empties[depth][0]
    x = empties[depth][1]
    if board[y][x] != 0:
        return dfs(depth+1)
    poss_blks = get_poss_blks(y, x)
    # 가망 없음
    if len(poss_blks) == 0:
        return False
    for block in poss_blks:
        idx = block[1][1]
        block[1][1] = 0
        blocks.pop(idx)

        # board 설정
        for i in range(2):
            for j in range(2):
                if -1 < x + j < 9 and -1 < y + i < 9:
                    board[y+i][x+j] += block[i][j]

        if dfs(depth+1):
            return True

        # board 설정 되돌리기
        for i in range(2):
            for j in range(2):
                if -1 < x + j < 9 and -1 < y + i < 9:
                    board[y+i][x+j] -= block[i][j]

        blocks.insert(idx, (block[0][0], block[0]
                      [1] if block[0][1] != 0 else block[1][0]))
    return False


loop_cnt = 1
while True:
    N = int(input())
    if N == 0:
        break
    board = [[0 for _ in range(9)]for _ in range(9)]
    blocks = gen_block()
    empties = []
    for _ in range(N):
        v1, pos1, v2, pos2 = input().split()
        v1 = int(v1)
        v2 = int(v2)
        board[get_yidx(pos1[0])][int(pos1[1]) - 1] = v1
        board[get_yidx(pos2[0])][int(pos2[1]) - 1] = v2
        blocks.remove((min([v1, v2]), max([v1, v2])))
    for idx, pos in enumerate(input().split()):
        board[get_yidx(pos[0])][int(pos[1]) - 1] = idx + 1

    for i in range(9):
        for j in range(9):
            if board[i][j] == 0:
                empties.append((i, j))

    dfs()
    print("Puzzle " + str(loop_cnt))
    for line in board:
        print(''.join([str(i) for i in line]))
    loop_cnt += 1
