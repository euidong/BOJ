import sys
input = sys.stdin.readline

N = int(input())
board = []

for _ in range(N):
    board.append([int(i) for i in input().split()])


def find_max(board):
    return max([max(line) for line in board])


dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def move(b, d):
    board = [line[:] for line in b]
    # 가로 이동
    if d % 2 == 0:
        for i in range(N):
            cursor = N-1 if d == 0 else 0
            idx = cursor
            while -1 < idx < N:
                if board[i][idx] != 0:
                    board[i][cursor], board[i][idx] = board[i][idx], board[i][cursor]
                    cursor -= dx[d]
                idx -= dx[d]
    else:
        for i in range(N):
            cursor = N-1 if d == 1 else 0
            idx = cursor
            while -1 < idx < N:
                if board[idx][i] != 0:
                    board[cursor][i], board[idx][i] = board[idx][i], board[cursor][i]
                    cursor -= dy[d]
                idx -= dy[d]
    return board


def merge(b, d):
    # 빈칸이 없다는 가정하에 수행
    board = [line[:] for line in b]

    if d % 2 == 0:
        for i in range(N):
            cursor = N-1 if d == 0 else 0
            r_s = 0 if d == 0 else -1
            r_e = N if d == 0 else N-1
            while r_s < cursor < r_e:
                if board[i][cursor] == board[i][cursor - dx[d]]:
                    board[i][cursor] *= 2
                    board[i][cursor-dx[d]] = 0
                    cursor -= dx[d] * 2
                else:
                    cursor -= dx[d]
    else:
        for i in range(N):
            cursor = N-1 if d == 1 else 0
            r_s = 0 if d == 1 else -1
            r_e = N if d == 1 else N-1
            while r_s < cursor < r_e:
                if board[cursor][i] == board[cursor - dy[d]][i]:
                    board[cursor][i] *= 2
                    board[cursor-dy[d]][i] = 0
                    cursor -= dy[d] * 2
                else:
                    cursor -= dy[d]
    return board


answer = find_max(board)

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]

q = [(board, 0)]

while len(q) > 0:
    board, depth = q.pop(0)
    for d in range(4):
        next_board = move(merge(move(board, d), d), d)
        answer = max([answer, find_max(next_board)])
        if depth < 4:
            q.append((next_board, depth + 1))

print(answer)
