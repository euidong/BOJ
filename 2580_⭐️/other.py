import sys


board = [list(map(int, input().split())) for _ in range(9)]
zeros = [(i, j) for i in range(9) for j in range(9) if board[i][j] == 0]


def get_possibles(r, c):
    possibles = set(range(1, 10))
    # row 삭제
    possibles -= set(board[r])
    test = set()
    for i in range(9):
        test.add(board[i][c])
    # column 삭제
    possibles -= test
    test = set()
    for i in range(r//3*3, r//3*3+3):
        for j in range(c//3*3, c//3*3+3):
            test.add(board[i][j])
    # square 삭제
    possibles -= test
    return tuple(possibles)


def solve(i):
    if i == len(zeros):
        [print(*row) for row in board]
        sys.exit()
    r, c = zeros[i]
    possibles = get_possibles(r, c)
    for num in possibles:
        board[r][c] = num
        solve(i+1)
        board[r][c] = 0


solve(0)
