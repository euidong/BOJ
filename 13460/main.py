import sys

input = sys.stdin.readline
N, M = map(int, input().split())
board = []

r = ()
b = ()
h = ()

for i in range(N):
    board.append(input().rstrip())
    for j in range(M):
        if board[i][j] == 'R':
            r = (i, j)
            board[i] = board[i].replace('R', '.')
        elif board[i][j] == 'B':
            b = (i, j)
            board[i] = board[i].replace('B', '.')
        elif board[i][j] == 'O':
            h = (i, j)

q = [(r, b, 0, -1)]

# right, down, left, up
dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def move(r, b, d):
    # r부터 체크
    cursor = r[:]
    in_b = False
    is_r_in_hole = False
    while True:
        if b[0] == cursor[0] and b[1] == cursor[1]:
            in_b = True
        if board[cursor[0]][cursor[1]] == '#':
            if in_b:
                return ((cursor[0] - 2 * dy[d], cursor[1] - 2 * dx[d]), (cursor[0] - dy[d], cursor[1] - dx[d])), None
            else:
                r = (cursor[0] - dy[d], cursor[1] - dx[d])
                break
        if board[cursor[0]][cursor[1]] == 'O':
            if in_b:
                return (r, b), False
            # 뒤쪽으로 b가 없으면 가능
            is_r_in_hole = True
            break
        cursor = (cursor[0] + dy[d], cursor[1] + dx[d])
    cursor = b[:]
    in_a = False
    while True:
        if r[0] == cursor[0] and r[1] == cursor[1]:
            in_a = True
        if board[cursor[0]][cursor[1]] == '#':
            if is_r_in_hole:
                return (r, b), True
            if in_a:
                return (r, (cursor[0] - 2 * dy[d], cursor[1] - 2 * dx[d])), None
            else:
                return (r,  (cursor[0] - dy[d], cursor[1] - dx[d])), None
        if board[cursor[0]][cursor[1]] == 'O':
            return (r, b), False

        cursor = (cursor[0] + dy[d], cursor[1] + dx[d])


while len(q) > 0:
    r, b, depth, prev_d = q.pop(0)
    if depth == 10:
        print(-1)
        break

    for d in range(4):
        if prev_d != -1 and (prev_d + 2) % 4 == d:
            continue
        (next_r, next_b), flag = move(r, b, d)
        if flag == None:
            q.append((next_r, next_b, depth + 1, d))
        elif flag:
            print(depth + 1)
            q = []
            break
