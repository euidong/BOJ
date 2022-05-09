import sys
from collections import deque

input = sys.stdin.readline

dy = [0, 1, 0, -1]
dx = [1, 0, -1, 0]


def get_dists(board, q, cnt):
    dists = [-1 for _ in range(cnt)]
    w = len(board[0])
    h = len(board)
    visited = [[False for _ in range(w)] for _ in range(h)]
    start = q[0][0]
    visited[start[0]][start[1]] = True
    dists[board[start[0]][start[1]]] = 0
    while len(q) > 0:
        (y, x), depth = q.popleft()
        for i in range(4):
            a = y + dy[i]
            b = x + dx[i]
            if -1 < a < h and -1 < b < w and not visited[a][b]:
                visited[a][b] = True
                if board[a][b] == 'x':
                    continue
                if board[a][b] != '.':
                    dists[board[a][b]] = depth + 1
                q.append(((a, b), depth + 1))
    return dists


tot_dists = []


def get_min_tot_dist(dists, visited, tot=0, cursor=0, depth=0):
    if depth == len(dists) - 1:
        tot_dists.append(tot)
        return
    adj_dists = dists[cursor]
    for adj in range(len(adj_dists)):
        if not visited[adj]:
            visited[adj] = True
            get_min_tot_dist(
                dists, visited, tot+adj_dists[adj], adj, depth + 1)
            visited[adj] = False


answers = []
while True:
    w, h = map(int, input().split())
    if w == h == 0:
        break
    # input 받기
    board = []
    qs = deque()
    cnt = 1
    for i in range(h):
        board.append([k for k in input().rstrip()])
        for j in range(w):
            if board[i][j] == 'o':
                board[i][j] = 0
                qs.appendleft(deque([((i, j), 0)]))
            if board[i][j] == '*':
                board[i][j] = cnt
                cnt += 1
                qs.append(deque([((i, j), 0)]))

    # 각 지점간 거리 구하기
    dists = []
    while len(qs) > 0:
        q = qs.popleft()
        dists.append(get_dists(board, q, cnt))

    # 최단 거리 들르면서 진행
    ok = True
    for i in range(len(dists[0])):
        if dists[0][i] == -1:
            ok = False
    if not ok:
        answers.append(-1)
    else:
        tot_dists = []
        visited = [False] * cnt
        visited[0] = True
        get_min_tot_dist(dists, visited)
        answers.append(min(tot_dists))


for a in answers:
    print(a)
