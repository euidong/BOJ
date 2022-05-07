from collections import deque
import sys
input = sys.stdin.readline
sys.setrecursionlimit(100000)

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def bfs(start):
    h = len(board)
    w = len(board[0])
    visited = [[False for _ in range(w)] for _ in range(h)]
    q = deque([(start, 0)])
    while len(q) > 0:
        (y, x), wall_cnt = q.popleft()
        if not visited[y][x]:
            visited[y][x] = True
            dfs(y, x, visited, h, w, wall_cnt, q)


def dfs(y, x, visited, h, w, wall_cnt, q):
    if scores[y][x] == -1:
        scores[y][x] = 0
    scores[y][x] += wall_cnt
    for i in range(4):
        a = y + dy[i]
        b = x + dx[i]
        if -1 < a < h and -1 < b < w and not visited[a][b]:
            visited[y][x] = True
            if board[a][b] == '.':
                dfs(a, b, visited, h, w, wall_cnt, q)
            elif board[a][b] == '#':
                q.append(((a, b), wall_cnt + 1))


answers = []
T = int(input())
for _ in range(T):
    h, w = map(int, input().split())
    board = []
    board.append(['.' for _ in range(w + 2)])
    prisoner = []
    for i in range(h):
        board.append(['.'] + [i for i in input().rstrip()] + ['.'])
    board.append(['.' for _ in range(w + 2)])
    for i in range(h+2):
        for j in range(w+2):
            if board[i][j] == '$':
                board[i][j] = '.'
                prisoner.append((i, j))

    scores = [[-1 for _ in range(w + 2)] for _ in range(h + 2)]
    bfs((0, 0))
    bfs(prisoner[0])
    bfs(prisoner[1])

    answer = 10000
    for i in range(h + 2):
        for j in range(w + 2):
            if board[i][j] == '*' or scores[i][j] == -1:
                continue
            temp = scores[i][j]
            if board[i][j] == '#':
                temp -= 2
            answer = min([answer, temp])
    answers.append(answer)

for answer in answers:
    print(answer)
