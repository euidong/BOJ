# Maximum 33% => Not Good
import sys
input = sys.stdin.readline

board = []
for _ in range(9):
    board.append([int(i) for i in input().split()])


def check_horizon(y, x):
    candidate = [True for _ in range(10)]
    candidate[0] = False
    competitor = []
    for i in range(9):
        v = board[y][i]
        if v != 0:
            candidate[v] = False
        elif i != x:
            competitor.append((y, i))
    return [candidate, competitor]


def check_vertical(y, x):
    candidate = [True for _ in range(10)]
    candidate[0] = False
    competitor = []
    for i in range(9):
        v = board[i][x]
        if v != 0:
            candidate[v] = False
        elif y != i:
            competitor.append((i, x))
    return [candidate, competitor]


def check_square(y, x):
    candidate = [True for _ in range(10)]
    candidate[0] = False
    y_idx = y // 3
    x_idx = x // 3
    competitor = []
    for i in range(y_idx * 3, y_idx * 3 + 3):
        for j in range(x_idx * 3, x_idx * 3 + 3):
            v = board[i][j]
            if v != 0:
                candidate[v] = False
            elif y != i and x != j:
                competitor.append((i, j))
    return [candidate, competitor]


def extract_dup(h, v, s):
    candidate = []
    for k in range(1, 10):
        if h[0][k] and v[0][k] and s[0][k]:
            candidate.append(k)
    return [candidate, h[1] + v[1] + s[1]]


visited = [[False for _ in range(9)] for _ in range(9)]


def dfs(y, x):
    h, v, s = check_horizon(y, x), check_vertical(y, x), check_square(y, x)
    candidates, competitors = extract_dup(h, v, s)
    # 가망 없음
    if len(candidates) == 0:
        return False
    # 후보자들 중에서 탐색
    for c in candidates:
        board[y][x] = c
        ok = True
        # 경쟁자 탐색
        for compet in competitors:
            if not visited[compet[0]][compet[1]]:
                visited[compet[0]][compet[1]] = True
                if not dfs(compet[0], compet[1]):
                    ok = False
                    break
        if not ok:
            for compet in competitors:
                visited[compet[0]][compet[1]] = False
            board[y][x] = 0
        else:
            return True
    # 모든 후보자를 탐색했지만, 불가능한 경우 - 가망 없음
    return False


def dfsAll():
    for i in range(9):
        for j in range(9):
            if not visited[i][j]:
                visited[i][j] = True
                if board[i][j] == 0:
                    dfs(i, j)


dfsAll()

for i in range(9):
    print(" ".join([str(j) for j in board[i]]))
