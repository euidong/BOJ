import sys
input = sys.stdin.readline

N, M, y, x, K = map(int, input().split())
board = []
for _ in range(N):
    board.append([int(i) for i in input().split()])

cmds = [int(i) for i in input().split()]


# x = 1, -x = -1, y = 2, -y = -2, z = 3, z = -3
# 1,2,3,4,5,6 index는 dice[index] = value 이고,
# dice[0] = (x의 index,y의 index, z의 index) 이다.
dice = [(3, 2, 1), 0, 0, 0, 0, 0, 0]


def move_west(dice):
    """
    west 이동했을 때, 주사위의 상태를 return
    """
    x_idx, y_idx, z_idx = dice[0]
    dice[0] = (7 - z_idx, y_idx, x_idx)
    return dice


def move_east(dice):
    """
    east 이동했을 때, 주사위의 상태를 return
    """
    x_idx, y_idx, z_idx = dice[0]
    dice[0] = (z_idx, y_idx, 7 - x_idx)
    return dice


def move_north(dice):
    """
    north 이동했을 때, 주사위의 상태를 return
    """
    x_idx, y_idx, z_idx = dice[0]
    dice[0] = (x_idx, z_idx, 7 - y_idx)
    return dice


def move_south(dice):
    """
    south 이동했을 때, 주사위의 상태를 return
    """
    x_idx, y_idx, z_idx = dice[0]
    dice[0] = (x_idx, 7 - z_idx, y_idx)


for cmd in cmds:
    ok = False
    if cmd == 1 and x + 1 < M:
        ok = True
        x += 1
        move_east(dice)
    elif cmd == 2 and x - 1 > -1:
        ok = True
        x -= 1
        move_west(dice)
    elif cmd == 3 and y - 1 > -1:
        ok = True
        y -= 1
        move_north(dice)
    elif cmd == 4 and y + 1 < N:
        ok = True
        y += 1
        move_south(dice)

    if ok:
        z_idx = dice[0][2]
        if board[y][x] == 0:
            board[y][x] = dice[7 - z_idx]
        else:
            dice[7-z_idx] = board[y][x]
            board[y][x] = 0
        print(dice[z_idx])
